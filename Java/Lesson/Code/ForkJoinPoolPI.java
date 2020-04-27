package OnlineJudge6;

import java.util.concurrent.RecursiveAction;// Without return
import java.util.concurrent.RecursiveTask;// With return
import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.RecursiveAction;
import java.util.concurrent.TimeUnit;


class PI extends RecursiveTask<Double>{
    int start,end;
    public PI(int start,int end){
        this.start=start;
        this.end=end;
        if(this.start%2==0){
            this.start++;
        }
    }

    @Override
    protected Double compute(){
        Double result=0.0;
        if(end-start>10){
            int mid=(start+end)/2;
            PI left=new PI(start,mid);
            PI right=new PI(mid,end);
            left.fork();
            right.fork();
            result=(Double)left.join()+(Double)right.join();
        }
        else{
            for(int i=start;i<=end;i+=2) {
                if (i % 4 == 1) {
                    result += (1.0 / i);
                } else {
                    result -= (1.0 / i);
                }
            }
        }
        return result;
    }
}
public class ForkJoinPoolPI {
    public static void main(String []args){
        ForkJoinPool forkJoinPool = new ForkJoinPool();
//        PI pi=new PI(1,128);
        Double result=(Double)forkJoinPool.invoke(new PI(1,65535));
//        Double result=(Double)forkJoinPool.invoke(pi);
        System.out.println(4*result);
        forkJoinPool.shutdown();
    }
}
