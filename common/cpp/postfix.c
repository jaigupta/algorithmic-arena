#include<stdio.h>
#include<string.h>
#define MAX 10000
char stack[MAX];
int top=-1;
char pop();
void push(char item);
inline int prcd(char symbol)
{
  switch(symbol)
  {
    case '+':
    case '-':return 2;
      break;
    case '*':
    case '/':return 4;
      break;
    case '^':
    case '$':return 6;
      break;
    case '(':
    case ')':
    case '#':return 1;
      break;
  }
}
inline void push(char item)
{
  top++;
  stack[top]=item;
}
inline char pop()
{
  char a;
  a=stack[top];
  top--;
  return a;
}
inline int isoperator(char symbol)
{
  switch(symbol)
  {
    case '+':
    case '-':
    case '*':
    case '/':
    case '^':
    case '$':
    case '(':
    case ')':return 1;
    break;
    default:return 0;
  }
}
inline void convertip(char infix[],char postfix[])
{
  int i,symbol,j=0;
  stack[++top]='#';
  for(i=0;i<strlen(infix);i++)
  {
    symbol=infix[i];
    if(isoperator(symbol)==0)
    {
      postfix[j]=symbol;
      j++;
    }
    else{
      if(symbol=='(')push(symbol);
      else if(symbol==')')
      {
        while(stack[top]!='(')
        {
          postfix[j]=pop();
          j++;
        }
        pop();//pop out (.
      }
      else{
        if(prcd(symbol)>prcd(stack[top]))
        push(symbol);
        else{
          while(prcd(symbol)<=prcd(stack[top]))
          {
            postfix[j]=pop();
            j++;
          }
          push(symbol);
        }//end of else.
      }//end of else.
    }//end of else.
  }//end of for.
  while(stack[top]!='#')
  {
    postfix[j]=pop();
    j++;
  }
  postfix[j]='\0';//null terminate string.
}
void main()
{
  int t,i;
  char infix[20000],postfix[20000];
  scanf("%d",&t);
  for(i=0;i<t;i++)
  {
    scanf("%s",infix);
    convertip(infix,postfix);
    puts(postfix);
  }
}


