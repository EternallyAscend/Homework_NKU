// package OnlineJudge;

import org.ietf.jgss.Oid;
import javax.crypto.AEADBadTagException;
import javax.crypto.Cipher;
import java.io.*;
import java.math.BigDecimal;
import java.security.*;
import java.security.interfaces.RSAPrivateKey;
import java.security.interfaces.RSAPublicKey;
import java.security.spec.PKCS8EncodedKeySpec;
import java.security.spec.X509EncodedKeySpec;
import java.util.*;
import java.util.function.ObjIntConsumer;

public class Bank{
    private String accountPath;
    private String publicKeyPath;
    private RSAPublicKey publicKey;
    Bank(){
        this.accountPath="account.txt";
        this.verifyExistFileOrCreateFile();
    }
    Bank(String accountPath,String publicKeyPath){
        this.accountPath=accountPath;
        this.publicKeyPath=publicKeyPath;
        this.verifyExistFileOrCreateFile();
    }

    public static void main(String []args){
        Bank bank=new Bank("accountCrypto.txt","publicKey.txt");
        boolean status=true;
        status=bank.createNewAccount("0000000000","Tom","RedHat");
        System.out.println(status);
        status= bank.createNewAccount("0000000001","Tommy","RedHat");
        System.out.println(status);
        status= bank.editAccountBalance("0000000000",new BigDecimal("110"));
        System.out.println(status);
        status= bank.editAccountBalance("0000000000",new BigDecimal("-1000"));
        System.out.println(status);
        bank.display();
    }

    protected synchronized boolean createNewAccount(String ID,String name,String key){
        try {
            String keyCrypto=sm(key);
            FileInputStream fileInputStream=new FileInputStream(this.accountPath);
            BufferedInputStream bufferedInputStream=new BufferedInputStream(fileInputStream);
            ObjectInputStream objectInputStream=new ObjectInputStream(bufferedInputStream);

            Accounts accounts=(Accounts)objectInputStream.readObject();

            objectInputStream.close();
            bufferedInputStream.close();
            fileInputStream.close();

            accounts.createAccount(ID,name,keyCrypto);

            FileOutputStream fileOutputStream=new FileOutputStream(this.accountPath);
            BufferedOutputStream bufferedOutputStream=new BufferedOutputStream(fileOutputStream);
            ObjectOutputStream objectOutputStream=new ObjectOutputStream(bufferedOutputStream);

            objectOutputStream.writeObject(accounts);

            objectOutputStream.close();
            bufferedOutputStream.close();
            fileOutputStream.close();
        }
        catch(Exception e){
            System.out.println(e.getMessage());
            return false;
        }
        return true;
    }

    protected synchronized boolean editAccountBalance(String ID,BigDecimal delta){
        try {
            FileInputStream fileInputStream=new FileInputStream(this.accountPath);
            BufferedInputStream bufferedInputStream=new BufferedInputStream(fileInputStream);
            ObjectInputStream objectInputStream=new ObjectInputStream(bufferedInputStream);

            Accounts accounts=(Accounts)objectInputStream.readObject();

            objectInputStream.close();
            bufferedInputStream.close();
            fileInputStream.close();

            accounts.editBalance(ID,delta);

            FileOutputStream fileOutputStream=new FileOutputStream(this.accountPath);
            BufferedOutputStream bufferedOutputStream=new BufferedOutputStream(fileOutputStream);
            ObjectOutputStream objectOutputStream=new ObjectOutputStream(bufferedOutputStream);

            objectOutputStream.writeObject(accounts);

            objectOutputStream.close();
            bufferedOutputStream.close();
            fileOutputStream.close();
        }
        catch(Exception e){
            System.out.println(e.getMessage());
            return false;
        }
        return true;
    }
    
    protected synchronized void display(){
        try{
            FileInputStream fileInputStream=new FileInputStream(this.accountPath);
            BufferedInputStream bufferedInputStream=new BufferedInputStream(fileInputStream);
            ObjectInputStream objectInputStream=new ObjectInputStream(bufferedInputStream);

            Accounts accounts=(Accounts)objectInputStream.readObject();
            accounts.showAccounts();

            objectInputStream.close();
            bufferedInputStream.close();
            fileInputStream.close();
        }
        catch(Exception e){

        }
    }

    protected synchronized void init(){
        try{
            KeyPairGenerator keyPairGenerator = KeyPairGenerator.getInstance("RSA");
            keyPairGenerator.initialize(1024);
            KeyPair keyPair = keyPairGenerator.generateKeyPair();
            RSAPublicKey rsaPublicKey = (RSAPublicKey) keyPair.getPublic();
            RSAPrivateKey rsaPrivateKey = (RSAPrivateKey) keyPair.getPrivate();

            this.publicKey=rsaPublicKey;

            FileOutputStream publicKeyFileOutputStream=new FileOutputStream(this.publicKeyPath);
            BufferedOutputStream publicKeyBufferedOutputStream=new BufferedOutputStream(publicKeyFileOutputStream);
            ObjectOutputStream publicKeyOutputStream=new ObjectOutputStream(publicKeyBufferedOutputStream);

            publicKeyOutputStream.writeObject(rsaPublicKey);

            publicKeyOutputStream.close();
            publicKeyBufferedOutputStream.close();
            publicKeyFileOutputStream.close();

            FileOutputStream fileOutputStream=new FileOutputStream(this.accountPath);
            BufferedOutputStream bufferedOutputStream=new BufferedOutputStream(fileOutputStream);
            ObjectOutputStream objectOutputStream=new ObjectOutputStream(bufferedOutputStream);

            objectOutputStream.writeObject(new Accounts(rsaPublicKey,rsaPrivateKey));

            objectOutputStream.close();
            bufferedOutputStream.close();
            fileOutputStream.close();
        }
        catch(Exception e){
            System.out.println("Create Failed.");
            System.out.println(e.getMessage());
        }
    }

    protected synchronized void verifyExistFileOrCreateFile(){
        Accounts accounts=null;
        RSAPublicKey puK=null;
        try{
            FileInputStream keyFileInputStream=new FileInputStream(this.publicKeyPath);
            BufferedInputStream keyBufferedInputStream=new BufferedInputStream(keyFileInputStream);
            ObjectInputStream keyObjectInputStream=new ObjectInputStream(keyBufferedInputStream);

            puK=(RSAPublicKey)keyObjectInputStream.readObject();

            keyObjectInputStream.close();
            keyBufferedInputStream.close();
            keyFileInputStream.close();

            FileInputStream fileInputStream=new FileInputStream(this.accountPath);
            BufferedInputStream bufferedInputStream=new BufferedInputStream(fileInputStream);
            ObjectInputStream objectInputStream=new ObjectInputStream(bufferedInputStream);

            accounts=(Accounts)objectInputStream.readObject();

            objectInputStream.close();
            bufferedInputStream.close();
            fileInputStream.close();

            this.publicKey=puK;

            if(accounts==null||puK==null){
                System.out.println("Account or public key doesn't exist.");
                this.init();
                System.out.println("Finished Init.");
            }
        }
        catch(Exception e){
            System.out.println("File Not Exist.");
            this.init();
            System.out.println("Finished Init.");
        }
    }

    /**
     * 二进制转换成16进制，加密后的字节数组不能直接转换为字符串
     */
    public static String parseByte2HexStr(byte buf[]) {
        StringBuffer sb = new StringBuffer();
        for (int i = 0; i < buf.length; i++) {
            String hex = Integer.toHexString(buf[i] & 0xFF);
            if (hex.length() == 1) {
                hex = '0' + hex;
            }
            sb.append(hex.toUpperCase());
        }
        return sb.toString();
    }

    /**
     * 16进制转换成二进制
     */
    public static byte[] parseHexStr2Byte(String hexStr) {
        if (hexStr.length() < 1)
            return null;
        byte[] result = new byte[hexStr.length() / 2];
        for (int i = 0; i < hexStr.length() / 2; i++) {
            int high = Integer.parseInt(hexStr.substring(i * 2, i * 2 + 1), 16);
            int low = Integer.parseInt(hexStr.substring(i * 2 + 1, i * 2 + 2), 16);
            result[i] = (byte) (high * 16 + low);
        }
        return result;
    }


    public static String sm(String key) throws Exception {
        //加密
        MessageDigest messageDigest = MessageDigest.getInstance("MD5");// 构建加密类型/SHA-512
        messageDigest.update(key.getBytes());// 传入要加密的字符串
        byte[] b = messageDigest.digest();
        String p = parseByte2HexStr(b);
        return p;
    }

    public static String cryptoWithPublicKey(RSAPublicKey rsaPublicKey,String information) throws Exception{
        X509EncodedKeySpec x509EncodedKeySpec = new X509EncodedKeySpec(rsaPublicKey.getEncoded());
        KeyFactory keyFactory = KeyFactory.getInstance("RSA");
        PublicKey publicKey = keyFactory.generatePublic(x509EncodedKeySpec);
        Cipher cipher = Cipher.getInstance("RSA");
        cipher.init(Cipher.ENCRYPT_MODE, publicKey);
        byte[] result = cipher.doFinal(information.getBytes());
        return new String(result);
    }
}
class AccountsException extends Exception{

    AccountsException(String message){
        super(message);
    }
    AccountsException(String message,String par){
        super(message);
        System.out.println(message+par);
    }
    AccountsException(String message,Accounts.Info info){
        super(message);
        System.out.println(info.name);
        System.out.println(info.ID);
        System.out.println(info.lastEdit);
    }
}
class Accounts implements Serializable{
    class Info implements Serializable{
        String ID;
        volatile String name;
        volatile String key;
//        BigDecimal balance;
        volatile String balanceCrypto;
        Date createDate;
        volatile Date lastEdit;
        protected Info(String ID,String name,String keyCrypto) throws Exception{
            this.ID=ID;
            this.createDate=new Date();
            this.editName(name);
            this.editKey(keyCrypto);
            this.editBalance(defaultZero);
//            this.editBalance("0.00");
        }
        protected synchronized void editName(String name) throws Exception{
            if(name.length()>40){
                throw new AccountsException("The name is too long.");
            }
            this.name=name;
            this.lastEdit=new Date();
        }
        protected synchronized void editKey(String keyCrypto){
            this.key=keyCrypto;
            this.lastEdit=new Date();
        }
        protected synchronized void editBalance(String newBalance){
            this.balanceCrypto=newBalance;
            this.lastEdit=new Date();
        }
        protected synchronized String getName(){
            return this.name;
        }
        protected synchronized String getKey(){
            return this.key;
        }
        protected synchronized String getBalanceCrypto(){
            return this.balanceCrypto;
        }
        protected synchronized void display() throws Exception{
            System.out.println("------------------------------");
            System.out.println(String.format("ID: %s.",this.ID));
            System.out.println(String.format("Name: %s.",this.getName()));
            System.out.println(String.format("Key: %s.",this.getKey()));
            System.out.println(String.format("Balance: %s.",this.getBalanceCrypto()));
            // System.out.println(String.format("Balance: %s.",decryptWithPrivateKey(balanceKey,this.balanceCrypto)));
            System.out.println("Create Date: "+this.createDate);
            System.out.println("Last Edit Time: "+this.lastEdit);
            System.out.println("------------------------------");
        }
    }
    HashMap<String,Info> accountList;
    RSAPublicKey balancePublicKey;
    RSAPrivateKey balanceKey;
    String defaultZero;
    Accounts(){
        this.accountList=new HashMap<String,Info>();
    }
    Accounts(RSAPublicKey balancePublickey,RSAPrivateKey balanceKey) throws Exception{
        this.balancePublicKey=balancePublickey;
        this.balanceKey=balanceKey;
        this.defaultZero=cryptoWithPublicKey(balancePublicKey,"0.00");
        this.accountList=new HashMap<String,Info>();
    }
    Accounts(RSAPublicKey balancePublickey,RSAPrivateKey balanceKey,String defaultZero){
        this.balancePublicKey=balancePublickey;
        this.balanceKey=balanceKey;
        this.defaultZero=defaultZero;
        this.accountList=new HashMap<String,Info>();
    }
    synchronized public void createAccount(String ID,String name,String keyCrypto) throws Exception{
        if(ID.length()>10){
            throw new AccountsException("The new ID is too long.");
        }
        if(this.accountList.containsKey(ID)){
            throw new AccountsException(String.format("Exist this ID %s already.",ID));
        }
        this.accountList.put(ID,new Info(ID,name,keyCrypto));
    }
    synchronized public void editBalance(String ID,BigDecimal delta) throws Exception{
        if(!this.accountList.containsKey(ID)){
            throw new AccountsException(String.format("Do not exist account with ID %s.",ID));
        }
        if(delta.equals(new BigDecimal("0.00"))){
            return;
        }
        String currentBalance=this.accountList.get(ID).getBalanceCrypto();
        // currentBalance to unCrypto
        currentBalance=decryptWithPrivateKey(this.balanceKey,currentBalance);
        BigDecimal current=new BigDecimal(currentBalance);
        if(delta.add(current).compareTo(new BigDecimal("0.00"))==-1){
            throw new AccountsException(String.format("Insufficient balance, exist %s, delta %s.",String.valueOf(current),String.valueOf(delta)));
        }
        current=current.add(delta);
        String newBalance=String.valueOf(current);
        // Crypto new balance.
        newBalance=cryptoWithPublicKey(this.balancePublicKey,newBalance);
        this.accountList.get(ID).editBalance(newBalance);
    }
    synchronized public void showAccounts(){
        try {
//            System.out.println(this.balancePublicKey);
//            System.out.println(this.balanceKey);
            for (String id : this.accountList.keySet()) {
                this.accountList.get(id).display();
            }
            System.out.println(String.format("Total Accounts %d.", this.accountList.size()));
        }
        catch(Exception e){
            e.printStackTrace();
        }
    }
    synchronized public Integer getAccountsNumber(){
        return this.accountList.size();
    }

    synchronized public static byte[] cryptoWithPublicKey(RSAPublicKey rsaPublicKey,byte[] information) throws Exception{
        X509EncodedKeySpec x509EncodedKeySpec = new X509EncodedKeySpec(rsaPublicKey.getEncoded());
        KeyFactory keyFactory = KeyFactory.getInstance("RSA");
        PublicKey publicKey = keyFactory.generatePublic(x509EncodedKeySpec);
        Cipher cipher = Cipher.getInstance("RSA");
        cipher.init(Cipher.ENCRYPT_MODE, publicKey);
        byte[] result = cipher.doFinal(information);
        return result;
    }
    synchronized public byte[] decryptWithPrivateKey(RSAPrivateKey rsaPrivateKey,byte[] information) throws Exception{
        byte[] info=information;
        PKCS8EncodedKeySpec pkcs8EncodedKeySpec = new PKCS8EncodedKeySpec(rsaPrivateKey.getEncoded());
        KeyFactory keyFactory = KeyFactory.getInstance("RSA");
        PrivateKey privateKey = keyFactory.generatePrivate(pkcs8EncodedKeySpec);
        Cipher cipher = Cipher.getInstance("RSA");
        cipher.init(Cipher.DECRYPT_MODE, privateKey);
        byte[] result = cipher.doFinal(info);
        return result;
    }


    public static String cryptoWithPublicKey(RSAPublicKey rsaPublicKey,String information) throws Exception{
        X509EncodedKeySpec x509EncodedKeySpec = new X509EncodedKeySpec(rsaPublicKey.getEncoded());
        KeyFactory keyFactory = KeyFactory.getInstance("RSA");
        PublicKey publicKey = keyFactory.generatePublic(x509EncodedKeySpec);
        Cipher cipher = Cipher.getInstance("RSA");
        cipher.init(Cipher.ENCRYPT_MODE, publicKey);
        byte[] result = cipher.doFinal(information.getBytes());
        return new String(parseByte2HexStr(result));
    }
    synchronized public String decryptWithPrivateKey(RSAPrivateKey rsaPrivateKey,String information) throws Exception{
        byte[] info=parseHexStr2Byte(information);
        PKCS8EncodedKeySpec pkcs8EncodedKeySpec = new PKCS8EncodedKeySpec(rsaPrivateKey.getEncoded());
        KeyFactory keyFactory = KeyFactory.getInstance("RSA");
        PrivateKey privateKey = keyFactory.generatePrivate(pkcs8EncodedKeySpec);
        Cipher cipher = Cipher.getInstance("RSA");
        cipher.init(Cipher.DECRYPT_MODE, privateKey);
        byte[] result = cipher.doFinal(info);
        return new String(result);
    }

    public static String parseByte2HexStr(byte buf[]) {
        StringBuffer sb = new StringBuffer();
        for (int i = 0; i < buf.length; i++) {
            String hex = Integer.toHexString(buf[i] & 0xFF);
            if (hex.length() == 1) {
                hex = '0' + hex;
            }
            sb.append(hex.toUpperCase());
        }
        return sb.toString();
    }

    public static byte[] parseHexStr2Byte(String hexStr) {
        if (hexStr.length() < 1)
            return null;
        byte[] result = new byte[hexStr.length() / 2];
        for (int i = 0; i < hexStr.length() / 2; i++) {
            int high = Integer.parseInt(hexStr.substring(i * 2, i * 2 + 1), 16);
            int low = Integer.parseInt(hexStr.substring(i * 2 + 1, i * 2 + 2), 16);
            result[i] = (byte) (high * 16 + low);
        }
        return result;
    }
}
