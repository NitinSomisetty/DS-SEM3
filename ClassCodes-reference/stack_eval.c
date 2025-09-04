#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<conio.h>

double compute(char x, double op1, double op2)
{
    if(x=='+')
        return(op1+op2);
    if(x=='-')
        return(op1-op2);
    if(x=='*')
        return(op1*op2);
    if(x=='/')
            return(op1/op2);
    if(x=='$')
            return pow(op1,op2);
}


void main()
{
	double s[20];
	char x;
	double op1,op2,val;
	int top;
	int i;
	char postfix[20];

    printf("Enter the postfix expression");
	scanf("%s",postfix);
	top=-1;

for(i=0;i<strlen(postfix);i++)
{
	x=postfix[i];
           if(isdigit(x))
              s[++top]=x-'0';      //x-'0' for removing the effect of ASCII(converts char representation of digit to equivalent int value)
        else
        {
            op2=s[top--];
            op1=s[top--];
            val=compute(x,op1,op2);
            s[++top]=val;
        }
}
    val=s[top--];
    printf("\nValue of expression=%f",val);
}
//123+*321-+*

