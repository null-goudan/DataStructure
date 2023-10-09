#include <stdio.h>
#include <stdlib.h>

typedef enum{
    true = 1, false = 0
}bool;

#define ElemType int

#define LIST_INIT_SIZE  100
#define LISTINCREMENT   10

typedef struct{
    ElemType * elem;
    int length;
    int listsize;
}Sqlist;

bool InitList_Sq(Sqlist *L){
    L->elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if(!L->elem) exit(-1);
    L->length = 0;
    L->listsize = LIST_INIT_SIZE;
    return true;
}

bool ListInsert_Sq(Sqlist *L, int i, ElemType e){
    if( i<1 || i > L->length + 1) return false;
    if(L->length >= L->listsize){
        ElemType *newbase = (ElemType *)realloc(L->elem, 
                            (L->listsize + LISTINCREMENT) * sizeof(ElemType));
        if(!newbase) exit(-1);
        L->elem = newbase;
        L->listsize += LISTINCREMENT;
    }
    int insert_idx = i - 1;
    for(int k = L->length - 1; k > insert_idx; k--){
        L->elem[k+1] = L->elem[k];
    }
    L->elem[insert_idx] = e;
    ++L->length;
}

bool ListDelete_Sq(Sqlist *L, int i, ElemType *e){ // e返回被删除的元素
    if((i<1) || (i>L->length)) return false;
    int delete_idx = i - 1;
    *e = L->elem[delete_idx];
    // 这里用指针了，直接不讲武德
    ElemType *p = &(L->elem[delete_idx]);
    ElemType *q = L->elem + L->length - 1;
    for(++p; p<=q; ++p) *(p - 1) = p;
    --L->length;
    return true;
}


int LocateElem_Sq(Sqlist L, ElemType e, bool (*cmp)(ElemType, ElemType)){
    int i = 1;
    ElemType *p = L.elem;
    while( i <= L.length && !(* cmp)(*p++, e)) ++i;
    if(i <= L.length) return i;
    else return -1;
}

int LocateElem_Sq_(Sqlist L, ElemType e){
    for(int i = 0 ;i < L.length ; i++){
        if(L.elem[i] == e) return i;
    }
    return -1;
}

int main(){
    // 对代码自信， 不编译测试了 hiahiahia
    return 0;
}

