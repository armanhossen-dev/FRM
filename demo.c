#include<stdio.h>
int main(){
    char name[50];
    scanf(" %[^\n]", name);
    printf("%s",name);
    return 0;
}