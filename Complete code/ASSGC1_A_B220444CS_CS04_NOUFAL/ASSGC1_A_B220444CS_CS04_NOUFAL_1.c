#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int isOperator(char a){
    if(a == '/' || a == '*' || a == '-' || a == '+' || a == '%'){
        return 1;
    }
    return 0;
}

int main(){
    int totalChar;
    scanf("%d", &totalChar);
    char str[totalChar];
    scanf("%s", str);
    char *stack = (char *)malloc((strlen(str) + 1) * sizeof(char));
    int top = -1;
    for(int i=0; i<strlen(str); i++){
        if(isOperator(str[i])){
            top++;
            stack[top] = str[i]; 
        }
        else if(str[i] == '('){
            top++;
            stack[top] = str[i];
        }
        else if(str[i] == ')'){
            if(stack[top] == '('){
                printf("1");
                return 1;
            }
            else{
                while(stack[top] != '('){
                    top--;
                }
                top--;
            }
        } 
    }
    printf("0");
    return 0;
}










