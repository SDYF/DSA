#include<stdio.h>
#include<stdlib.h>

struct phone_n {
    int lab;
    int phone_number;
    long phone_charge;
}


int main(){
    FILE *fp;
    char str[23];
    int loc;

    fp= fopen("records.txt","r")
    phone_n *phone;
    phone=(phone *)malloc(1000000*sizeof(phone_n));

    while(fgets(str,30,fp)!=NULL){
        

    }




    free(phone);


}


