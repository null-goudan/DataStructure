#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10

typedef int ElemType;

typedef enum{
    OK = 0,
    ERROR = -1
}Status;

typedef enum{
    true = 1,
    false = 0
}bool;

typedef struct 
{
    ElemType *elem;
    int length;
    int listsize;
}SqList;

Status InitList_Sq(SqList* L){
    L->elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if(!L->elem) exit(ERROR);
    L->length = 0;
    L->listsize - LIST_INIT_SIZE;
    return OK;
}// InitList_Sq

Status DestroyList_Sq(SqList* L){
    free(L->elem);
    free(L);
    return OK;
}// DestroyList_Sq

Status ClearList(SqList* L){
    ElemType* p = L->elem;
    ElemType* end = L->elem + L->length - 1;
    if(!p || !end) return ERROR;
    while(p!=end){
        *p = 0;
        ++p;
    }
    L->length = 0;
    return OK;
}

bool ListEmpty_Sq(SqList* L){
    return L->length == 0;
}

int ListLength_Sq(SqList* L){
    return L->length;
}

Status GetElem_Sq(SqList* L, int i, ElemType* e){
    if(i<0||i>L->length-1) return ERROR;
    *e = L->elem[i];
    return OK;
}

Status ListInsert_Sq(SqList *L, int i, ElemType e){
    if(i < 1 || i > L->length+1) return ERROR;
    if(L->length >= L->listsize){
        ElemType* newbase = (ElemType*)realloc(L->elem, (L->listsize + LIST_INIT_SIZE) *sizeof(ElemType));
        if(!newbase) exit(ERROR);
        L->elem = newbase;
        L->listsize += LISTINCREMENT;
    }
    ElemType* q = &(L->elem[i-1]);
    for(ElemType* p = &(L->elem[L->length-1]);p>=q; --p) *(p-1) = *p;
    *q = e;
    ++L->length;
    return OK;
}// ListInsert_Sq

Status ListDelete_Sq(SqList *L, int i, ElemType e){
    if(i < 0 || i > L->length) return ERROR;
    ElemType *p = &(L->elem[i]);
    e = *p;
    ElemType *q = L->elem + L->length;
    for(++p;p<=q;++p) *(p-1) = *p;
    -- L->length;
    return OK;
}//ListDelete_Sq

bool compare(ElemType a, ElemType b){return a == b;}

int LocateElem_Sq(SqList *L, ElemType e,bool (*compare)(ElemType, ElemType)){
    int i = 0;
    ElemType* p = L->elem;
    while(i< L->length && (* compare)(*p++, e)) i++;
    if(i<=L->length) return i;
    else return 0;
}// LocateElem_Sq

void ListPrint_Sq(SqList *L){
    ElemType* p = L->elem;
    ElemType* q = L->elem + L->length;
    while(p!=q){
        printf("%d ",*p++);
    }
    printf("\n");
}

// test
int main(){
    SqList L;
    Status r = InitList_Sq(&L);
    printf("is empty: %d, length: %d\n", ListEmpty_Sq(&L), ListLength_Sq(&L));
    ListInsert_Sq(&L, 1, 1);
    ListInsert_Sq(&L, 2, 2);
    printf("is empty: %d, length: %d\n", ListEmpty_Sq(&L), ListLength_Sq(&L));
    ListDelete_Sq(&L, 1, 1);
    ListDelete_Sq(&L, 1, 2);
    printf("is empty: %d, length: %d\n", ListEmpty_Sq(&L), ListLength_Sq(&L));
    ListPrint_Sq(&L);
    return 0;
}


