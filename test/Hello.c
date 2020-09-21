#include<stdio.h>
#include<stdlib.h>
int sum(int**,int);
int sym(int**,int);
int spa(int**,int);
int main(){
    int n=0,a=0; int i,j;
    int **A;
    scanf("%d",&n);
    A=(int**)malloc(sizeof(int*)*n);
    for (i=0;i<n;i++) A[i]=(int*)malloc(sizeof(int)*n);
    for (i=0;i<n;i++) 
        for (j=0;j<n;j++) 
            scanf("%d",&A[i][j]);

  /*  for (i=0;i<n;i++){ 
        for (j=0;j<n;j++) 
            printf("%d ",A[i][j]);
    printf("\n");
    }
 */
//  sum(A,n);
//  sym(A,n);
    spa(A,n);
}

int sum(int**A,int n){
    int i=0,sum_l=0,sum_c=0;
    for (i=0;i<n;i++){
        sum_l+=*(*(A+i)+i);
        sum_c+=*(*(A+i)+n-i-1);
    }
    printf("%d %d\n",sum_l,sum_c);

}

int sym(int**A,int n){
    int i=0,j=0; 
    for (i=0;i<n-1;i++)
        for (j=i+1;j<n;j++)
        if (*(*(A+i)+j)!=*(*(A+j)+i)) {
            printf("No!\n");
            return(0);
        }
        printf("Yes!\n");
        return(0);
}

int spa(int**A,int n){
    int i=0,j=0; double p=0;
    for (i=0;i<n;i++)
        for (j=0;j<n;j++)
            if (*(*(A+i)+j)!=0) p++;
    
    if (p/(n*n)<0.05) printf("Yes\n"); else printf("No\n");
    printf("%f\n",p/(n*n));

    return(0);
    
}