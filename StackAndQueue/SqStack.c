#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef int Elemtype;

typedef enum{
    OK = 0,
    ERROR = -1
}Status;

typedef enum{
    true = 1,
    false = 0
}bool;

typedef struct{
    Elemtype* base;
    Elemtype* top;
    int stacksize;  // malloc size
}SqStack;

Status InitStack(SqStack* S);
Status DestroyStack(SqStack* S);
Status ClearStack(SqStack* S);
bool StackEmpty(SqStack S);
int StackLength(SqStack S);
Status Top(SqStack S, Elemtype* e);
Status Push(SqStack *S, Elemtype e);
Status Pop(SqStack *S, Elemtype *e);
Status StackTraverse(SqStack S, Status (*visit)());

Status printE(Elemtype e){
    printf("%d\t", e);
    return OK;
}

int main(){
    SqStack S;
    InitStack(&S);
    if(StackEmpty(S)) printf("Empty\n");
    for(int i = 0;i<5;i++){
        Push(&S, i);
    }
    StackTraverse(S, printE);
    printf("\n");
    return 0;
}


Status InitStack(SqStack* S){
    S->base = (Elemtype *) malloc(sizeof(Elemtype)* STACK_INIT_SIZE);
    if(S->base==NULL) return ERROR;
    S->top = S->base;
    S->stacksize = STACK_INIT_SIZE;
    return OK;
}

Status DestroyStack(SqStack* S){
    free(S->base);
    free(S);
}

Status ClearStack(SqStack* S){
    S->top = S->base;
}

bool StackEmpty(SqStack S){
    return S.top == S.base;
}

int StackLength(SqStack S){
    return S.top - S.base;
}

Status Top(SqStack S, Elemtype* e){
    *e = *S.top;
}

Status Push(SqStack *S, Elemtype e){
    *S->top++ = e;
}

Status Pop(SqStack *S, Elemtype *e){
    *e = *S->top--;
}

Status StackTraverse(SqStack S, Status (*visit)(Elemtype)){
    while(!StackEmpty(S)){
        Elemtype e;
        Pop(&S,&e);
        visit(e);
    }
}