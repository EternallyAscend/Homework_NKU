package JShell;

import java.math.BigDecimal;
import java.util.*;

public class J_Shell {
    static char[] operator ={'+','-','*','/','%','(',')'};
    static Map<String,Integer> operatorLevel =new HashMap<String,Integer>();
    static{
        operatorLevel.put("#",0);
        operatorLevel.put("+",20);
        operatorLevel.put("-",20);
        operatorLevel.put("*",40);
        operatorLevel.put("/",40);
        operatorLevel.put("%",40);
        operatorLevel.put("(",100);
        operatorLevel.put(")",100);
    }

//    static HashMap<String,Integer> variableInteger=new HashMap<String,Integer>();
//    static HashMap<String,Float> variableFloat=new HashMap<String,Float>();
    static HashMap<String,String> variableList=new HashMap<String, String>();
    static Vector<String> expression=new Vector<String>();

    public static void defineVariable(String inputLine){
        int head,middle,tail;
        head=middle=tail=0;
        inputLine=inputLine.replaceAll(" ","");
        if(inputLine.contains("int")){
            inputLine=inputLine.substring(inputLine.indexOf("int")+3,inputLine.length()-1+1);
//            System.out.println(inputLine);
            for(int i=0;i<inputLine.length();i++){
                if(inputLine.charAt(i)=='='){
                    middle=i;
                }
                if(inputLine.charAt(i)==','||inputLine.charAt(i)==';'){
                    tail=i;
                    String name="";
                    if(middle==0){
                        name=inputLine.substring(head,tail);
                        variableList.put(name,"Null_Integer");

//                        System.out.println("Define "+name+" as a Null Integer.");
                    }
                    else{
                        name=inputLine.substring(head,middle);
                        String value=inputLine.substring(middle+1,tail);
                        int valueTemp=Integer.parseInt(value);
                        value=String.valueOf(valueTemp);
                        variableList.put(name,value);

//                        System.out.println("Define "+name+" as "+value);
                    }
                    head=i+1;
                    middle=0;
                }
            }
//            System.out.println(inputLine);
            //Null_Integer
        }
        else if(inputLine.contains("float")){
            inputLine=inputLine.substring(inputLine.indexOf("float")+5,inputLine.length()-1+1);
            for(int i=0;i<inputLine.length();i++){
                if(inputLine.charAt(i)=='='){
                    middle=i;
                }
                if(inputLine.charAt(i)==','||inputLine.charAt(i)==';'){
                    tail=i;
                    String name="";
                    if(middle==0){
                        name=inputLine.substring(head,tail);
                        variableList.put(name,"Null_Float");

//                        System.out.println("Define "+name+" as a Null Float.");
                    }
                    else{
                        name=inputLine.substring(head,middle);
                        String value=inputLine.substring(middle+1,tail);
                        float valueTemp=Float.parseFloat(value);
                        value=String.valueOf(valueTemp);
                        variableList.put(name,value);

//                        System.out.println("Define "+name+" as "+value);
                    }
                    head=i+1;
                    middle=0;
                }
            }
//            System.out.println(inputLine);
            //Null_Float
        }
    }
    public static boolean assignVariable(String inputline){
        int head,middle,tail;
        head=middle=tail=0;
//        boolean defined=true;
        for(int i=head;i<inputline.length();i++){
            if(inputline.charAt(i)=='='){
                middle=i;
            }
            if(inputline.charAt(i)==','||inputline.charAt(i)==';'){
                tail=i;
                String name=inputline.substring(head,middle);
                String value=inputline.substring(middle+1,tail);
//                System.out.println(name+" "+value);
                if(variableList.containsKey(name)){//System.out.println(variableList.get(name));
                    if(variableList.get(name).contains("Null_Float")||variableList.get(name).contains(".")){
                        variableList.remove(name,value);
                        variableList.put(name,String.valueOf(Float.parseFloat(value)));
                    }
                    else if(variableList.get(name).contains("Null_Integer")||!variableList.get(name).contains(".")){
                        variableList.remove(name,value);
                        variableList.put(name,value);//System.out.println("Assign"+value);
                    }
                }
                else{return false;}
                head=i+1;
            }
        }
        return true;
    }
    public static boolean checkExpression(Vector<String> expression){
        int lastOperator=-1;
        for(int i=0;i<expression.size();i++){
            for(int j = 0; j< operator.length-2; j++){
                if(expression.get(i).equals(operator[j])){
                    if(i-lastOperator<=1){
                        return false;
                    }
                    else{
                        lastOperator=i;
                    }

                }
            }
        }
        if(lastOperator==expression.size()-1){
            if(lastOperator!=-1){return false;}
        }
        //Check continuous operators;
        for(int i=0;i<expression.size();i++){
            if(expression.get(i).equals("/")){
                if(i+1<expression.size()){
                    if(Float.parseFloat(expression.get(i+1))==0){
                        return false;
                    }
                }
            }
        }
        //Check divided zero.

        return true;
    }
    public static boolean bracketsMatching(String inputLine){
        Stack<Character> brackets=new Stack<Character>();
        for(int i=0;i<inputLine.length();i++){
            if(inputLine.charAt(i)=='('){
                brackets.push('(');
            }
            else if(inputLine.charAt(i)==')'){
                if(brackets.empty()||brackets.peek().equals(')')){
                    return false;
                }
                else if(brackets.peek().equals('(')){
                    brackets.pop();
                }
            }
        }
        return (brackets.empty());
    }
    public static String replaceVariableWithNumber(Vector<String> expression){
        Vector<String> Cache=new Vector<String>();
        for(int i=0;i<expression.size();i++){
            boolean operators=false;
            for(int j=0;j<operator.length;j++){
                if(expression.get(i).equals(String.valueOf(operator[j]))){
                    operators=true;
                    break;
                }
            }
            if(!operators){
                if(variableList.containsKey(String.valueOf(expression.get(i)))){
                    if(variableList.get(expression.get(i)).contains("Null")){
                        return "wrong - variable unassigned";
                    }
//                    System.out.println("Replace "+expression.get(i)+" as "+variableList.get(expression.get(i)));
                    Cache.addElement(String.valueOf(variableList.get(expression.get(i))));
                }
                else{
                    boolean isNumber=true;
                    for(int k=0;k<expression.get(i).length();k++){
                        if(!Character.isDigit(expression.get(i).charAt(k))&&expression.get(i).charAt(k)!='.'){
                            isNumber=false;
                        }
                    }
                    if(!isNumber) {
//                        System.out.println("There is not this value." + expression.get(i));
                        return "wrong - variable undefined";
                    }
                    else{
                        Cache.addElement(expression.get(i));
                    }
                }
            }
            else{
                Cache.addElement(expression.get(i));
            }
        }
        expression.clear();
        expression.addAll(Cache);
        return "true";
    }

    public static String processing(Vector<String> inputList,Vector<String> resultList){
        String result="";
        for(String inputLine:inputList){
//            System.out.println(inputLine);
            expression.clear();
//            judgeDefine(s,resultList);
            if(inputLine.contains("int ")||inputLine.contains("float ")){
//                System.out.println("Define");
                defineVariable(inputLine);
//            return true;
            }
            else {
                if(inputLine.contains("?")){
                    boolean syntax=bracketsMatching(inputLine);
                    if(!syntax){return "wrong - error expression";}
                    replaceOfExpression(inputLine,expression);
//                    for(String s:expression){
//                        System.out.println(s);
//                    }
                    String variableDefined=replaceVariableWithNumber(expression);
//                    System.out.println(variableDefined);
                    if(!variableDefined.equals("true")){
                        return variableDefined;
                    }
//                    for(String s:expression){
//                        System.out.println(s);
//                    }
                    boolean math=checkExpression(expression);
                    if(!math){System.out.println("Math");return "wrong - error expression";}
                    //Checking the syntax here.
                    infixToPolish(expression);
                    calcuatePolian(expression);
                    for(String k:expression){
                        resultList.add(k);
                    }
//                return false;
                }
                else{
                    if(!assignVariable(inputLine)){
                        return "wrong - variable undefined";
                    }
//                return true;
                }
            }
        }
        return result;
    }


    public static boolean judgeFloat(String inputString){
        return inputString.contains(".");
    }
    public static void replaceOfExpression(String inputString, Vector<String> expression){
        inputString=inputString.replaceAll(" ","");
        inputString=inputString.replaceAll("=","");

        inputString=inputString.replace("?","");
        int start=0,end=-1;
        for(int i=0;i<inputString.length();i++){
            for(int j = 0; j< operator.length; j++){
                if(inputString.charAt(i)== operator[j]){
                    end=i;
                    if(end>=start+1){
                        expression.add(inputString.substring(start,end));
                    }
                    expression.add(String.valueOf(operator[j]));
                    start=i+1;
                    break;
                }
            }
            end++;
        }
        if(end>=start+1){
            expression.add(inputString.substring(start,end));
        }
        if(end==start+inputString.length()-1&&start==0){
            expression.addElement(inputString);
        }
    }
    public static void infixToPolish(Vector<String> expression){
        int brackets=0;
        Stack<String> operatorTemp=new Stack<String>();
        Stack<String> numberTemp=new Stack<String>();
        operatorTemp.push("#");
        for(int i=expression.size()-1;i>=0;i--){
            boolean operatorBool=false;
            for(int j = 0; j< operator.length; j++){
                if(expression.get(i).equals(String.valueOf(operator[j]))){
                    operatorBool=true;
                    if(expression.get(i).equals(String.valueOf(")"))){
                        brackets++;
                        operatorTemp.push(")");
//                        System.out.println("Push )");
                        break;
                    }
                    if(expression.get(i).equals(String.valueOf("("))){
                        while(!operatorTemp.peek().equals(")")){
                            numberTemp.push(operatorTemp.pop());
                        }
                        operatorTemp.pop();
//                        System.out.println("Pop (");
                        brackets--;
                        break;
                    }
                    if(brackets>0){int value=operatorLevel.get(expression.get(i));
                        while(value<operatorLevel.get(operatorTemp.peek())&&operatorLevel.get(operatorTemp.peek())<operatorLevel.get(")")){
                            numberTemp.push(operatorTemp.pop());
                        }
                        operatorTemp.push(expression.get(i));
                        break;
                    }
                    else{
                        int value=operatorLevel.get(expression.get(i));
                        while(value<operatorLevel.get(operatorTemp.peek())){
                            numberTemp.push(operatorTemp.pop());
                        }
                        operatorTemp.push(expression.get(i));
                        break;
                    }
                }
            }
            if(!operatorBool){
                numberTemp.push(expression.get(i));
            }
        }
        expression.clear();
        while(!operatorTemp.peek().equals("#")){
            numberTemp.push(operatorTemp.pop());
        }
        while(!numberTemp.empty()){
            expression.add(numberTemp.pop());
        }
    }
    public static void calcuatePolian(Vector<String> expression){
//        float temp=0;
//        Stack<String> operatorTemp=new Stack<String>();
        Stack<String> resultTemp=new Stack<String>();
        for(int i=expression.size()-1;i>=0;i--){
            boolean operatorBool=false;
            for(int j = 0; j< operator.length; j++){
                if(expression.get(i).equals(String.valueOf(operator[j]))){
                    operatorBool=true;
                    boolean xIF=judgeFloat(resultTemp.peek());
                    float x=0,y=0;
                    x=Float.parseFloat(resultTemp.pop());
                    boolean yIF=judgeFloat(resultTemp.peek());
                    y=Float.parseFloat(resultTemp.pop());
                    if(xIF||yIF) {
                        float temp=0;
//                        System.out.println(x+" "+y);
//                        System.out.println("Float"+xIF+yIF);
                        temp = (calcuateFloat(expression.get(i), x, y));
//                        BigDecimal b = new BigDecimal(temp);
//                        temp = b.setScale(2,BigDecimal.ROUND_HALF_UP).floatValue();
//                        String sss = String.format("%1.2f", temp);
                        resultTemp.push(String.valueOf(temp));
                    }
                    else{
                        int temp=0;
//                        System.out.println(x+" "+y);
//                        System.out.println("Int"+xIF+yIF);
                        temp=(calcuateInterger(expression.get(i),(int)x,(int)y));
                        resultTemp.push(String.valueOf((int)temp));
                    }
                    break;
                }
            }
            if(!operatorBool){
                resultTemp.push(expression.get(i));
            }
        }
        expression.clear();
//        expression.add(resultTemp.pop());
        for(String s:resultTemp){
            if(s.contains(".")){
                expression.addElement(String.format("%1.2f",Float.parseFloat(s)));
            }
            else{
                expression.addElement(s);
            }
        }
    }
    public static float calcuateFloat(String operator,float x,float y){
        switch (operator){
            case "%":
                return x%y;
            case "+":
                return x+y;
            case "-":
                return x-y;
            case "*":
                return x*y;
            case "/":
                return x/y;
            default:
                return 0;
        }
    }
    public static int calcuateInterger(String operator,int x,int y){
        switch (operator){
            case "%":
                return x%y;
            case "+":
                return x+y;
            case "-":
                return x-y;
            case "*":
                return x*y;
            case "/":
                return x/y;
            default:
                return 0;
        }
    }


    public static void main(String[] args){
        Scanner JShellScanner=new Scanner(System.in);
        Vector<String> inputList=new Vector<String>();
        Vector<String> resultList=new Vector<String>();
        while(JShellScanner.hasNext()){
            inputList.add(JShellScanner.nextLine());
        }
//        for(String s:inputList){
//            System.out.println(s);
//        }
//        System.out.println("_______________________________________________________");
        String result=processing(inputList,resultList);
        if(result.contains("wrong")){
            System.out.println(result);
            return;
        }
        if(result.equals(""))
        {
            for(String s:resultList){
                System.out.println(s);
            }
        }
    }
}

//如果表达式错误，则输出wrong - error expression
//变量未定义，则输出 wrong - variable undefined
//变量未赋初值，则输出  wrong - variable unassigned

//float b=1;
//b=?
//int a=21;
//int b=2;
//float c=11;
//a/b+c=?

//int i;
//int j;
//i=10;
//j=20;
//i*2+j=?
//i+j=?



//    int m=2;
//    int j=10;
//    m+(m-b)*2=?

//    int m;
//int j=10;
//m=10;
//m=2;
//m=?


//    float j;
//float a;
//j=10;
//a=3;
//j/a*3=?


//    float j;
//float a;
//j=10;
//a=3;
//j/a=?