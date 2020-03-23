import java.util.*;

public class Eval {
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
    static public void eval(String inputString){
        boolean floatOrNot=judgeFloat(inputString);
        Vector<String> expression=new Vector<String>();
        replace(inputString,expression);
        infixToPolish(expression);
//        for(String s:expression){
//            System.out.print(s+" ");
//        }
        calcuatePolian(expression,floatOrNot);
        for (String s : expression) {
            System.out.println(s);
        }
    }
    public static boolean judgeFloat(String inputString){
        return inputString.contains(".");
    }
    public static void replace(String inputString,Vector<String> expression){
        inputString=inputString.replaceAll(" ","");
        inputString=inputString.replaceAll("=","");
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
    public static void calcuatePolian(Vector<String> expression, boolean floatOrNot){
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
        expression.add(resultTemp.pop());
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
    public static void main(String []args){
        Scanner input=new Scanner(System.in);
        String inputString=input.nextLine();
        eval(inputString);
    }
}

//2+3/2*3-4*(2+5-2*4/2+9)+3+(2*1)-3=
//9*(20-1)-(1+199)
//(5*5)%11*(9+2)
//19.2+8.67/3=