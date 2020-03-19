package lottery;
import java.io.File;
import java.io.IOException;
import java.lang.reflect.Array;
import java.util.*;

import java.util.jar.JarEntry;
import java.util.jar.JarFile;
import java.io.File;
import java.net.URL;
import java.net.URLClassLoader;

class SingleChoose extends Lottery{
    static{Lottery.playList.put("SingleChoose",new SingleChoose());}

    @Override
    public int getWinLevel() {
        boolean same=true;
        for(int i=0;i<3;i++) {
            if(Ans[i]!=input[i]){
                same=false;
                break;
            }
        }
        if(same){return 1040;}
        else return 0;
    }
}

class GroupThree extends Lottery{
    static{Lottery.playList.put("GroupThree",new GroupThree());}

    int winNumber1,winNumber2,inputNumber1,inputNumber2;
    @Override
    public void createAns() {
        super.createAns();
        Random GroupThreeSeed=new Random();
        int GroupThreePosition0=GroupThreeSeed.nextInt(3);
        int GroupThreePosition1=GroupThreeSeed.nextInt(3);
        while(GroupThreePosition0==GroupThreePosition1){
            GroupThreePosition0=GroupThreeSeed.nextInt(3);
            GroupThreePosition1=GroupThreeSeed.nextInt(3);
        }
        this.Ans[GroupThreePosition0]=this.Ans[GroupThreePosition1];
        this.winNumber1=this.Ans[3-GroupThreePosition0-GroupThreePosition1];
        this.winNumber2=this.Ans[GroupThreePosition0];
    }

    @Override
    public boolean getInput() {
        System.out.println("Please input the number with two same number and one different.");
        Scanner GroupThreeInput=new Scanner(System.in);
        int GroupThreeInputNumber=GroupThreeInput.nextInt();
        if(GroupThreeInputNumber>=1000||GroupThreeInputNumber<0){return false;}
        this.input=new int[3];
        super.sliceOfNumber(GroupThreeInputNumber,this.input);
        int GroupThreeCounter=0;
        for(int i=0;i<2;i++){
            for(int j=i+1;j<3;j++){
                if(this.input[i]==this.input[j]){
                    GroupThreeCounter++;
                    this.inputNumber2=this.input[i];
                    this.inputNumber1=this.input[3-i-j];
                }
            }
        }
        return (GroupThreeCounter==1);
    }

    @Override
    public int getWinLevel() {
        if(this.inputNumber1==this.winNumber1&&this.inputNumber2==this.winNumber2){return 346;}
        else return 0;
    }
}

class GroupSix extends Lottery{
    static{Lottery.playList.put("GroupSix",new GroupSix());}

    @Override
    public void createAns() {
        this.Ans=new int[3];
        Random GroupSixSeed=new Random();
        this.Ans[0]=GroupSixSeed.nextInt(10);
        this.Ans[1]=GroupSixSeed.nextInt(10);
        this.Ans[2]=GroupSixSeed.nextInt(10);
        while(this.Ans[1]==this.Ans[0]){this.Ans[1]=GroupSixSeed.nextInt(10);}
        while(this.Ans[2]==this.Ans[1]||this.Ans[2]==this.Ans[0]){this.Ans[0]=GroupSixSeed.nextInt(10);}
    }

    @Override
    public boolean getInput() {
        System.out.println("Please input the integer between 0 and 999 without same number.");
        Scanner inputNumber=new Scanner(System.in);
        int inputNum=inputNumber.nextInt();
        if(inputNum<1000&&inputNum>=0){
            this.input=new int[3];
            sliceOfNumber(inputNum,this.input);
            for(int i=0;i<2;i++){
                for(int j=i+1;j<3;j++){
                    if(this.input[i]==this.input[j]){return false;}
                }
            }
            return true;
        }
        else{return false;}
    }

    @Override
    public int getWinLevel() {
        Arrays.sort(this.Ans);
        Arrays.sort(this.input);
        for(int i=0;i<3;i++){
            if(this.Ans[i]!=this.input[i]){return 0;}
        }
        return 173;
    }
}

class OneDChoose extends Lottery{
    static{Lottery.playList.put("OneDChoose",new OneDChoose());}
    char[] inputChar;
    int OneDChooseGuessPosition;
    @Override
    public boolean getInput() {
        System.out.println("Please input one number between 0 to 9 with two \"*\".");
        Scanner OneDChooseScanner=new Scanner(System.in);
        inputChar=new char[3];
        this.input=new int[3];
        String inputCharString=OneDChooseScanner.nextLine();
        inputCharString=inputCharString.replaceAll(" ","");
        if(inputCharString.length()!=3){return false;}
        int OneDChooseStarCounter=0;
        for(int i=0;i<3;i++){
            if(inputCharString.charAt(i)=='*'||(inputCharString.charAt(i)>='0'&&inputCharString.charAt(i)<='9')){
                inputChar[i]=inputCharString.charAt(i);
                if(inputChar[i]=='*'){
                    OneDChooseStarCounter++;
                    this.input[i]=-1;
                }
                else {
                    OneDChooseGuessPosition=i;
                    this.input[i]=Integer.parseInt(String.valueOf(inputChar[i]));
                }
            }
            else return false;
        }
        if(OneDChooseStarCounter==2){return true;}
        else return false;
    }

    @Override
    public int getWinLevel() {
        if(this.Ans[OneDChooseGuessPosition]==this.input[OneDChooseGuessPosition]){return 10;}
        else return 0;
    }
}

class OneDGuess extends Lottery{
    static{Lottery.playList.put("OneDGuess",new OneDGuess());}

    @Override
    public boolean getInput() {
        System.out.println("Please input the number you guess which need between 0 to 9.");
        Scanner OneDGuessScanner=new Scanner(System.in);
        this.input=new int[1];
        this.input[0]=OneDGuessScanner.nextInt();
        if(this.input[0]>9||this.input[0]<0){return false;}
        else return true;
    }

    @Override
    public int getWinLevel() {
        int level=0;
        for(int i=0;i<3;i++){
            if(this.Ans[i]==this.input[0]){level++;}
        }
        if(level==1){return 2;}
        if(level==2){return 12;}
        if(level==3){return 230;}
        return level;
    }
}

class TwoDChoose extends Lottery{
    static{Lottery.playList.put("TwoDChoose",new TwoDChoose());}
    char[] inputChar;
    int TwoDChooseGuessPosition0=-1;
    int TwoDChooseGuessPosition1=-1;
    @Override
    public boolean getInput() {
        System.out.println("Please input two number between 0 to 9 with a \"*\".");
        Scanner OneDChooseScanner=new Scanner(System.in);
        inputChar=new char[3];
        this.input=new int[3];
        String inputCharString=OneDChooseScanner.nextLine();
        inputCharString=inputCharString.replaceAll(" ","");
        if(inputCharString.length()!=3){return false;}
        int OneDChooseStarCounter=0;
        for(int i=0;i<3;i++){
            if(inputCharString.charAt(i)=='*'||(inputCharString.charAt(i)>='0'&&inputCharString.charAt(i)<='9')){
                inputChar[i]=inputCharString.charAt(i);
                if(inputChar[i]=='*'){
                    OneDChooseStarCounter++;
                    this.input[i]=-1;
                }
                else {
                    if(TwoDChooseGuessPosition0==-1){TwoDChooseGuessPosition0=i;}
                    if(TwoDChooseGuessPosition0!=-1){TwoDChooseGuessPosition1=i;}
                    this.input[i]=Integer.parseInt(String.valueOf(inputChar[i]));
                }
            }
            else return false;
        }
        if(OneDChooseStarCounter==1){return true;}
        else return false;
    }

    @Override
    public int getWinLevel() {
        if(this.Ans[TwoDChooseGuessPosition0]==this.input[TwoDChooseGuessPosition0]&&this.Ans[TwoDChooseGuessPosition1]==this.input[TwoDChooseGuessPosition1]){return 104;}
        else return 0;
    }
}

class TwoDGuess extends Lottery{
    static{Lottery.playList.put("TwoDGuess",new TwoDGuess());}

    @Override
    public boolean getInput() {
        System.out.println("Please input two number which between 0 to 9.");
        Scanner TwoGuessScanner=new Scanner(System.in);
        int tempNumber=TwoGuessScanner.nextInt();
        if(tempNumber>99||tempNumber<0){return false;}
        this.input=new int[2];
        this.input[0]=tempNumber/10;
        this.input[1]=tempNumber%10;
        return true;
    }

    @Override
    public int getWinLevel() {
        int counter=0;
        if(this.input[0]==this.input[1]){
            for(int i=0;i<3;i++){
                if(this.Ans[i]==this.input[0]){
                    counter++;
                }
            }
            if(counter>1){return 37;}
        }
        else{
            for(int i=0;i<3;i++){
                if(this.Ans[i]==this.input[0]||this.Ans[i]==this.input[1]){counter++;}
            }
            if(counter==2){return 19;}
        }
        return 0;
    }
}

class GeneralChoose extends Lottery{
    static{Lottery.playList.put("GeneralChoose",new GeneralChoose());}

    @Override
    public int getWinLevel() {
        int GeneralCounter=0;
        for(int i=0;i<3;i++){
            if(this.Ans[i]==this.input[i]){GeneralCounter++;}
        }
        if(GeneralCounter==3){return 470;}
        else if(GeneralCounter==2){return 21;}
        else return 0;
    }
}

class Sum extends Lottery{
    static{Lottery.playList.put("Sum",new Sum());}

    int[] resultList={1040,345,172,104,69,49,47,29,23,19,16,15,15,14};

    @Override
    public boolean getInput() {
        System.out.println("Please input the sum of the number between 0 to 27.");
        Scanner SumScanner=new Scanner(System.in);
        this.input=new int[1];
        this.input[0]=SumScanner.nextInt();
        return (this.input[0] <= 27 && this.input[0] >= 0);
    }

    @Override
    public int getWinLevel() {
        if(this.input[0]==this.Ans[0]+this.Ans[1]+this.Ans[2]){
            if(this.input[0]>13){this.input[0]=27-this.input[0];}
            return resultList[this.input[0]];
        }
        else return 0;
    }
}

class PackageChoose extends Lottery{
    static{Lottery.playList.put("PackageChoose",new PackageChoose());}

    @Override
    public int getWinLevel() {
        int PackageCounter=0;
        for(int i=0;i<2;i++){
            for(int j=i+1;j<3;j++){
                if(this.input[i]==this.input[j]){
                    PackageCounter++;
                }
            }
        }
        boolean total=true;
        for(int i=0;i<3;i++){
            if(this.Ans[i]!=this.input[i]){total=false;}
        }
        boolean all=true;
        Arrays.sort(this.Ans);
        Arrays.sort(this.input);
        for(int i=0;i<3;i++){
            if(this.Ans[i]!=this.input[i]){all=false;}
        }
        if(total){
            if(PackageCounter==0){return 606;}
            else return 693;
        }
        if(all){
            if(PackageCounter==0){return 86;}
            else return 173;
        }
        return 0;
    }
}

class GuessBigOrSmall extends Lottery{
    static{Lottery.playList.put("GuessBigOrSmall",new GuessBigOrSmall());}

    @Override
    public boolean getInput() {
        System.out.println("Please input number from [0,8] and [19,27].");
        Scanner BigSmall=new Scanner(System.in);
        this.input=new int[1];
        this.input[0]=BigSmall.nextInt();
        if(this.input[0]<0||this.input[0]>27||(this.input[0]>8&&this.input[0]<19)){return false;}
        return true;
    }

    @Override
    public int getWinLevel() {
        int SumBigSmall=0;
        if(this.input[0]>18){this.input[0]=20;}
        else{this.input[0]=0;}
        for(int i=0;i<3;i++){
            SumBigSmall+=this.Ans[i];
        }
        if(SumBigSmall>18){SumBigSmall=20;}
        else if(SumBigSmall<9){SumBigSmall=0;}
        if(SumBigSmall==this.input[0]){return 6;}
        return 0;
    }
}

class GuessSameThree extends Lottery{
    static{Lottery.playList.put("GuessSameThree",new GuessSameThree());}

    @Override
    public boolean getInput() {
        return true;
    }

    @Override
    public int getWinLevel() {
        if(this.Ans[0]==this.Ans[1]&&this.Ans[1]==this.Ans[2]){return 104;}
        else return 0;
    }
}

class Serial extends Lottery{
    static{Lottery.playList.put("Serial",new Serial());}

    @Override
    public boolean getInput() {
        return true;
    }

    @Override
    public int getWinLevel() {
        if(this.Ans[0]-this.Ans[1]==this.Ans[1]-this.Ans[2]){
            if(Math.abs(this.Ans[0]-this.Ans[1])==1) {
                return 65;
            }
        }
        return 0;
    }
}

class GuessOddOrEven extends Lottery{
    static{Lottery.playList.put("GuessOddOrEven",new GuessOddOrEven());}

    @Override
    public boolean getInput() {
        System.out.println("Please input a number in order to mean odd or even such as 0 and 1. Please Smaller than 1000.");
        Scanner OddAndEvenScanner=new Scanner(System.in);
        this.input=new int[1];
        this.input[0]=OddAndEvenScanner.nextInt();
        return (this.input[0]>=0&&this.input[0]<1000);
    }

    @Override
    public int getWinLevel() {
        boolean odd=true;
        boolean even=true;
        for(int i=0;i<3;i++){
            if(this.Ans[i]%2==0){odd=false;}
            else{even=false;}
        }
        if(odd){
            if(this.input[0]%2==1){return 8;}
        }
        if(even){
            if(this.input[0]%2==0){return 8;}
        }
        return 0;
    }
}

class LotteryManager{
    public static boolean checkPlayList(String userInput){
        Lottery temp=Lottery.playList.get(userInput);
        if (temp==null){
            try{
                Class.forName("lottery."+userInput);//Get from the ini file?
                return true;
            }
            catch(Exception e){
                return false;
            }
        }
        return true;
    }
}

public abstract class Lottery{
    int []Ans;
    int []input;
    protected static Map<String,Lottery> playList=new HashMap();
    public void setAns(int []ans){
        this.Ans=ans;
    }
//    public static void getAllMethod(){
//        Iterator iter = hashMap.entrySet().iterator();
//        while (iter.hasNext()) {
//            Map.Entry entry = (Map.Entry) iter.next();
//            Object key = entry.getKey();
//            Object value = entry.getValue();
//            System.out.println(key + ":" + value);
//
//        }
////        System.out.println(this.getClass().getName());
//    }
    public void sliceOfNumber(int number,int []list){
        list[2]=number%10;
        list[1]=(number/10)%10;
        list[0]=(number/100);
    }
    public void createAns(){
        Random seed=new Random();
        this.Ans=new int[3];
        sliceOfNumber(seed.nextInt(1000),this.Ans);
    }
    public void outputAns(){
        System.out.print("The winning number is:");
        for(int i=0;i<Ans.length;i++){
            System.out.print(" "+this.Ans[i]);
        }
        System.out.println();
    }
    public boolean getInput(){
        System.out.println("Please input the integer between 0 and 999.");
        Scanner inputNumber=new Scanner(System.in);
        int inputNum=inputNumber.nextInt();
        if(inputNum<1000&&inputNum>=0){
            this.input=new int[3];
            sliceOfNumber(inputNum,this.input);
            return true;
        }
        else{return false;}
    }
    public abstract int getWinLevel();

    public static List<String> getClassName(String packageName,boolean childPackage){
        List<String> fileNames = null;
        ClassLoader loader = Thread.currentThread().getContextClassLoader();
        String packagePath = packageName.replace(".", "/");
        URL url = loader.getResource(packagePath);
        if (url != null) {
            String type = url.getProtocol();
            if (type.equals("file")) {
                fileNames = getClassNameByFile(url.getPath(), null, childPackage);
            } else if (type.equals("jar")) {
                fileNames = getClassNameByJar(url.getPath(), childPackage);
            }
        } else {
            fileNames = getClassNameByJars(((URLClassLoader) loader).getURLs(), packagePath, childPackage);
        }
        return fileNames;
    }

    private static List<String> getClassNameByFile(String filePath, List<String> className, boolean childPackage) {
        List<String> myClassName = new ArrayList<>();
        File file = new File(filePath);
        File[] childFiles = file.listFiles();
        for (File childFile : childFiles) {
            if (childFile.isDirectory()) {
                if (childPackage) {
                    myClassName.addAll(getClassNameByFile(childFile.getPath(), myClassName, childPackage));
                }
            } else {
                String childFilePath = childFile.getPath();
                if (childFilePath.endsWith(".class")) {
                    childFilePath = childFilePath.substring(childFilePath.indexOf("\\classes") + 9,
                            childFilePath.lastIndexOf("."));
                    childFilePath = childFilePath.replace("\\", ".");
                    myClassName.add(childFilePath);
                }
            }
        }

        return myClassName;
    }

    private static List<String> getClassNameByJar(String jarPath, boolean childPackage) {
        List<String> myClassName = new ArrayList<>();
        String[] jarInfo = jarPath.split("!");
        String jarFilePath = jarInfo[0].substring(jarInfo[0].indexOf("/"));
        String packagePath = jarInfo[1].substring(1);
        try {
            JarFile jarFile = new JarFile(jarFilePath);
            Enumeration<JarEntry> entrys = jarFile.entries();
            while (entrys.hasMoreElements()) {
                JarEntry jarEntry = entrys.nextElement();
                String entryName = jarEntry.getName();
                if (entryName.endsWith(".class")) {
                    if (childPackage) {
                        if (entryName.startsWith(packagePath)) {
                            entryName = entryName.replace("/", ".").substring(0, entryName.lastIndexOf("."));
                            myClassName.add(entryName);
                        }
                    } else {
                        int index = entryName.lastIndexOf("/");
                        String myPackagePath;
                        if (index != -1) {
                            myPackagePath = entryName.substring(0, index);
                        } else {
                            myPackagePath = entryName;
                        }
                        if (myPackagePath.equals(packagePath)) {
                            entryName = entryName.replace("/", ".").substring(0, entryName.lastIndexOf("."));
                            myClassName.add(entryName);
                        }
                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return myClassName;
    }

    private static List<String> getClassNameByJars(URL[] urls, String packagePath, boolean childPackage) {
        List<String> myClassName = new ArrayList<>();
        if (urls != null) {
            for (int i = 0; i < urls.length; i++) {
                URL url = urls[i];
                String urlPath = url.getPath();
                if (urlPath.endsWith("classes/")) {
                    continue;
                }
                String jarPath = urlPath + "!/" + packagePath;
                myClassName.addAll(getClassNameByJar(jarPath, childPackage));
            }
        }
        return myClassName;
    }

    public static void main(String args[]) throws Exception{

        String packageName = "lottery";
        List<String> classNames = getClassName(packageName, false);
        if (classNames != null) {
            int counters=0;
            for (String className : classNames) {
                if(className.contains("Lottery")){continue;}
                if(counters%5==0){System.out.println();}
                counters++;
                System.out.print(className.substring(className.lastIndexOf('.')+1,className.length())+" ");
            }
            System.out.println();
        }
//        Class a = Class.forName("lottery.Lottery");
//        Class b = null;
//        System.out.println(a.getClass().getName());
//        while ((b = a.getSuperclass()) != null) {
//            a = b;
//            System.out.println(b);
//        }

//        Iterator iter = playList.entrySet().iterator();
//        while (iter.hasNext()) {
//            Map.Entry entry = (Map.Entry) iter.next();
//            Object key = entry.getKey();
//            Object value = entry.getValue();
//            System.out.println(key + ":" + value);
//
//        }
        Scanner termialInput=new Scanner(System.in);
        System.out.println("Please input the bets way. Input 0 to exit.");
        while(termialInput.hasNext()){
            String userInput=termialInput.nextLine();
            if(userInput.contains("0")){//userInput.indexOf("0")!=-1;
                System.out.println("Bye-bye.");
                break;
            }
            else{
                if(LotteryManager.checkPlayList(userInput)){
                    Lottery temp= Lottery.playList.get(userInput);
                    temp.createAns();
                    temp.outputAns();
                    while(true){
                        if(temp.getInput()){
                            System.out.println("You win "+temp.getWinLevel()+".");
                            break;
                        }
                        else{
                            System.out.println("Please input correct betting content. Please try again.");
                            continue;
                        }
                    }
                }
                else{
                    System.out.println("You need to input correct bets way. Please try again.");
                    continue;
                }
            }
            if (classNames != null) {
                int counters=0;
                for (String className : classNames) {
                    if(className.contains("Lottery")){continue;}
                    if(counters%5==0){System.out.println();}
                    counters++;
                    System.out.print(className.substring(className.lastIndexOf('.')+1,className.length())+" ");
                }
                System.out.println();
            }
            System.out.println("Please input the bets way. Input 0 to exit.");
        }
    }
}
