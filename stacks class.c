#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


struct node
{

    int data;
        struct node *next;

};
struct stack
{
    struct node *top;

};
void initstack(struct stack *s);
void push(struct stack *s, int e);
int isEmpty(struct stack *s);
int pop(struct stack *s);
int peek(struct stack *s);

int main() {

    struct stack s;
    initstack(&s);
    int e,ch;

    while(1)
    {

    scanf("%d",&ch);

switch(ch){
    case 1: printf("enter elements:");
            scanf("%d",&e);
            push(&s,e);
            break;
    case 2:    if(isEmpty(&s))
            printf("stack underflow:");
               else{
            e=pop(&s);
            printf("%d\n", e);
            }break;
    case 3:    if(isEmpty(&s))
            printf("stack underflow:");
               else{
            e=peek(&s);
            printf("%d\n", e);
             }break;
    case -1:  exit(0);

}
    }
}

  void initstack(struct stack *s)
  {
      s->top=NULL;
  }
    void push(struct stack *s, int e)
    {
       struct node *p;
        p=(struct node *)malloc(sizeof(struct node));
        if (p==NULL){
            perror("stack overflow\n");
            return;
        }
    p->data=e;
    p->next=s->top;
     s->top=p;
 }
    int isEmpty(struct stack *s) {
        if(s->top==NULL)
            return 1;
        else
            return 0;

    }
       int pop(struct stack *s)
       {
           int e;
           struct node *p=s->top;
           s->top=p->next;
           e=p->data;
           free(p);
           return e;
       }

       int peek(struct stack *s)
         {
             struct node *p=s->top;
             return p->data;
        }









