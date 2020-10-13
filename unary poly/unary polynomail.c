#include<stdio.h>
#include<stdlib.h>

struct ElemType {
    double coe;
    int exp;
};

struct LNode {
    struct ElemType data;
    struct LNode *next;
};

int main(){
    
    char lab='\0'; int count=0,lab_1=0; 

    while(1){
        printf("请输入需要执行的项目(1~)：");
        printf("1.创建多项式        2.打印显示多项式\n");
        printf("3.销毁多项式        4.复制多项式\n");
        printf("5.求两个多项式的和        6.求两个多项式的差\n");
        printf("7.求两个多项式的积        8.求一个多项式的n次幂\n");
        printf("9.计算一个多项式在x=a处的值\n ");
        printf("0.退出程序");
        
//等待后续添加；
        lab_1=0;
        lab=getchar();
        if (getchar()!='\n'){
            lab_1=1;
            while(getchar()!='\n') continue;
        if (lab_1) { printf("错误输入！\n"); continue;

        switch (lab)
        {
        case '1':
            //创建多项式；
        
        default:
            printf("错误输入！\n");
            break;
        }
        



    }
}


