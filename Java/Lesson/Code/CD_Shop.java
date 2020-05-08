import java.util.*;
import java.io.*;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingDeque;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintStream;
import java.util.zip.ZipEntry;
import java.util.zip.ZipOutputStream;

class Shop extends Thread{
    class ShopPool extends ThreadPoolExecutor{

        public ShopPool(int corePoolSize, int maximumPoolSize, long keepAliveTime, TimeUnit unit, BlockingQueue<Runnable> workQueue) {
            super(corePoolSize, maximumPoolSize, keepAliveTime, unit, workQueue);
            this.ThreadList=new Vector<MyThread>();
        }

        @Override
        public void execute(Runnable command) {
            try {
                if (command.getClass().getSuperclass().getName().equals(this.temp.getClass().getName())) {
                    this.ThreadList.add((MyThread) command);
                }
            }
            catch (Exception ignored){
                System.out.println("--------------------------------");
            }
            super.execute(command);
        }

        @Override
        public void shutdown() {
            for(int i=0;i<this.ThreadList.size();i++){
                try{
                    this.ThreadList.get(i).Stop();
                }
                catch(Exception ignored){
                    System.out.println("--------------------------------------");
                }
            }
            try {
                writeRecord("--------------------------------------");
            }
            catch(IOException ignored) {

            }
            super.shutdown();
        }

        Vector<MyThread> ThreadList;
        MyThread temp=new MyThread();

    }
    Shop(int Rent,int SellType,int SellSize,int RentThread,int SellThread,long SustainTime,String filePath,String fileName) throws Exception {
        this.record=new File(filePath+fileName+".txt");
        if(!this.record.exists()){
            this.record.createNewFile();
        }
        this.fileWriter=new FileWriter(this.record.getName(),true);
        this.rent=Rent;
        this.sellType=SellType;
        this.sellSize=SellSize;
        this.rentThread=RentThread;
        this.sellThread=SellThread;
        this.sustainTime=SustainTime;
        this.rentList=new Vector<Boolean>();
        this.sellList=new Vector<Integer>();
        for(int i=0;i<Rent;i++){
            this.rentList.add(true);
        }
        for(int j=0;j<SellType;j++){
            this.sellList.add(SellSize);
        }
        this.threadPoolExecutor=new ShopPool(8,Integer.MAX_VALUE,0, TimeUnit.MILLISECONDS,new LinkedBlockingDeque<Runnable>());
    }

    @Override
    public void run() {
        super.run();
        this.timerForShop=new TimerForShop(true);
        try {
            this.fileWriter.write("--- ------------ ---"+this.operator);
            this.fileWriter.write(String.valueOf(System.currentTimeMillis())+this.operator);
        } catch (IOException e) {
            e.printStackTrace();
        }
        timerForShop.schedule(new Stock(),0L,1000L);
        for(int i=0;i<this.rentThread;i++) {
            this.threadPoolExecutor.execute(new Renter());
        }
        for(int i=0;i<this.sellThread;i++){
            this.threadPoolExecutor.execute(new Customer());
        }
        try {
            Thread.sleep(this.sustainTime);
            this.fileWriter.write(System.currentTimeMillis()+this.operator);
            this.stopAllThread();
            this.interrupt();
            this.fileWriter.write(System.currentTimeMillis()+this.operator);
        } catch (InterruptedException e) {
            e.printStackTrace();
        } catch (Exception e){
            e.getMessage();
        }
    }
    File record;
    FileWriter fileWriter;
    String operator=System.getProperty("line.separator");
    long sustainTime;
    int rent;
    int sellType;
    int sellSize;
    int rentThread;
    int sellThread;
    Vector<Boolean> rentList;
    Vector<Integer> sellList;
    Shop.TimerForShop timerForShop;
    ShopPool threadPoolExecutor;

    protected synchronized void writeRecord(String Content) throws IOException {
        this.fileWriter.write(Content+this.operator);
    }

    protected synchronized int getRandomRentNumber(){
        return (int)(Math.random()*this.rent);
    }

    protected synchronized int getRandomSellNumber(){
        return (int)(Math.random()*this.sellType);
    }

    protected synchronized int getRandomSizeNumber(){
        return (int)(Math.random()*5)+1;
    }

    protected synchronized void stockCD() throws IOException {
        for(int i=0;i<this.sellType;i++){
            if(this.sellList.get(i)<this.sellSize){
                this.sellList.setElementAt(this.sellSize,i);
            }
        }
        this.fileWriter.write("Stock all CDs."+this.operator);
    }

    protected synchronized boolean rentCD(int Number) throws IOException {
        if (this.rentList.get(Number)) {
            this.rentList.setElementAt(false, Number);
            this.fileWriter.write("Rent CD "+Number+" Successfully."+this.operator);
            return true;
        } else {
            this.fileWriter.write("Rent failed for lack of CD " + Number+this.operator);
            return false;
        }
    }

    protected synchronized boolean returnCD(int Number) throws IOException {
        if(this.rentList.get(Number)){
            this.fileWriter.write("Return CD "+Number+" false."+this.operator);
            return false;
        }
        else {
            this.rentList.setElementAt(true, Number);
            this.fileWriter.write("Return CD "+Number+this.operator);
            return true;
        }
    }

    protected synchronized boolean sellCD(int Type,int Count) throws IOException {
        if(this.sellList.get(Type)<Count){
            new Stock().run();
            return false;
        }
        else{
            this.sellList.setElementAt(this.sellList.get(Type)-Count,Type);
            this.fileWriter.write("Sell "+Type+" "+Count+" Remaining "+this.sellList.get(Type)+this.operator);
            return true;
        }
    }

    public void stopAllThread() throws Exception {
        this.threadPoolExecutor.shutdown();
        this.fileWriter.write("Time up! Stop accepting new operation."+this.operator);
        while(this.threadPoolExecutor.getActiveCount()>0){
            Thread.sleep(1L);
        }
        this.fileWriter.write("All Done."+this.operator);
        this.fileWriter.close();
    }

    class TimerForShop extends Timer{
        TimerForShop(boolean isDaemon){
            super(isDaemon);
        }
    }

    class Stock extends TimerTask{

        @Override
        public void run() {
            try {
                stockCD();
            }
            catch (Exception ignored){
            }
        }
    }

    class MyThread extends Thread{
        volatile boolean running;
        MyThread(){
            super();
            this.running=true;
        }
        public void Stop(){
            this.running=false;
        }

        @Override
        public void run() {
            super.run();
        }
    }
    class Renter extends MyThread{
        volatile boolean running;
        Renter() {
            super();
            this.running=true;
        }
        public void Stop(){
            this.running=false;
        }
        @Override
        public void run() {
            while(this.running){
                boolean get=true;
                int rentNumber;
                rentNumber=getRandomRentNumber();
                try {
                    while (!rentCD(rentNumber)) {
                        double waitOrQuit;
                        waitOrQuit = Math.random();
                        if (waitOrQuit >= 0.5) {
                            try {
                                this.sleep(100L);
                                writeRecord("Rent " + rentNumber + " Waiting.");
                            } catch (InterruptedException e) {
                                e.printStackTrace();
                            }
                        } else {
                            writeRecord("Rent " + rentNumber + " Give up and Exit.");
                            get = false;
                            break;
                        }
                    }
                }
                catch(Exception ignored){

                }
                long sleepTime;
                if(get) {
                    sleepTime=(long)(Math.random()*100);
                    try {
                        Thread.sleep(sleepTime+200L);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                    try {
                        returnCD(rentNumber);
                    }
                    catch(Exception ignored){

                    }
                }
                sleepTime=(long)(Math.random()*200);
                try {
                    Thread.sleep(sleepTime);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    class Customer extends MyThread{
        volatile boolean running;
        Customer() {
            super();
            this.running=true;
        }
        public void Stop(){
            this.running=false;
        }
        @Override
        public void run() {
            while(this.running){
                int purchaseNumber;
                purchaseNumber=getRandomSellNumber();
                int purchaseSize;
                purchaseSize=getRandomSizeNumber();
                try {
                    while (!sellCD(purchaseNumber, purchaseSize)) {
                        double waitOrQuit;
                        waitOrQuit = Math.random();
                        if (waitOrQuit >= 0.5) {
                            try {
                                writeRecord("Sell CD " + purchaseNumber + " " + purchaseSize + " Waiting.");
                                this.sleep(100L);
                            } catch (InterruptedException e) {
                                e.printStackTrace();
                            }
                        } else {
                            writeRecord("Sell " + purchaseNumber + " " + purchaseSize + " Give up Exit.");
                            break;
                        }
                    }
                }
                catch(Exception ignored){

                }
                long sleepTime;
                sleepTime=(long)(Math.random()*200);
                try {
                    Thread.sleep(sleepTime);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}

public class CD_Shop {

    public static void main(String[] args) throws Exception {
        OnlineJudge6.Shop shop = new OnlineJudge6.Shop(10, 10, 10, 5, 5, 120000L,"./","record");
        shop.start();
        shop.join();
    }
}