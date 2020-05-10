#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<iostream>
using namespace std;
int main(void){
    unsigned int index;
    scanf("%d",&index); 
    int flag=index;
    flag=flag<<1;
    int layer=(int)(sqrt(flag));
    int now=pow(layer,2)+layer;
    while(now<flag){
        now+=(++layer)<<1;
    }
    index=layer-((now-flag)>>1)-1;
     if(layer%2==0){
        printf("%d/%d\n",index+1,layer-index);
    }
    else{
        printf("%d/%d\n",layer-index,index+1);
    }
    return 0;
}
