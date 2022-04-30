#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum{
    OK = 0,
    ERROR = -1
}Status;

typedef enum{
    true = 1,
    false = 0
}bool;

typedef int Elemtype;

typedef struct LNode{
    Elemtype data;
    struct LNode* next;
}LNode, *PLNode;

Status CreateNode_Lk(Elemtype e, PLNode newnode);

typedef struct{
    PLNode headnode;
    int length;
}LinkList;

Status InitList_Lk(LinkList* L);
Status DestroyList_Lk(LinkList* L);
Status ClearList_Lk(LinkList* L);
bool ListEmpty_Lk(LinkList* L);
int ListLength_Lk(LinkList* L);
Status GetElem_Lk(LinkList* L, int i, Elemtype* e);
int LocateElem_Lk(LinkList* L, Elemtype* e, bool (*compare)(Elemtype, Elemtype));
Status ListInsert_Lk(LinkList* L, int i, Elemtype e);
Status ListDelete_Lk(LinkList* L, int i, Elemtype* e);

int main(){

}

Status CreateNode_Lk(Elemtype e, PLNode newnode){
    newnode = (PLNode)malloc(sizeof(LNode));
    if(newnode==NULL) return ERROR;
    newnode->data = e;
    newnode->next = NULL;
    return OK;
}

Status InitList_Lk(LinkList* L){
    L = (LinkList *)malloc(sizeof(LinkList));
    if(L == NULL) return ERROR;
    L->headnode = NULL;
    L->length = 0;
    return OK;
}

Status DestroyList_Lk(LinkList* L){
    if(L==NULL) return ERROR;
    PLNode pnode = L->headnode;
    PLNode pdeletenode = NULL;
    if(pnode == NULL) return ERROR;
    while(pnode){
        pdeletenode = pnode;
        pnode = pnode->next;
        free(pdeletenode);
    }
    L->length = 0;
    free(L);
    return OK;
}

Status ClearList_Lk(LinkList* L){
    if(L==NULL) return ERROR;
    PLNode pnode = L->headnode;
    PLNode pdeletenode = NULL;
    if(pnode == NULL) return OK;
    while(pnode){
        pdeletenode = pnode;
        pnode = pnode->next;
        free(pdeletenode);
    }
    L->length = 0;
    L->headnode = NULL;
    return OK;
}

bool ListEmpty_Lk(LinkList* L){
    return L->length == 0;
}

int ListLength_Lk(LinkList* L){
    return L->length;
}

Status GetElem_Lk(LinkList* L, int i, Elemtype* e){
    if(i<0||i>L->length) return ERROR;
    PLNode pnode = L->headnode;
    while(pnode&&i) pnode = pnode->next, --i;
    if(pnode==NULL) return ERROR;
    *e = pnode->data;
    return OK;
}

bool cmp(Elemtype a, Elemtype b){
    return a==b;
}

int LocateElem_Lk(LinkList* L, Elemtype* e, bool (*compare)(Elemtype, Elemtype)){
    if(L==NULL) return ERROR;
    int i = 0;
    PLNode pnode = L->headnode;
    for(i = 0;pnode&&compare(pnode->data, *e);++i) pnode = pnode->next;
    if(pnode==NULL) return ERROR;
    return i;
}

Status ListInsert_Lk(LinkList* L, int i, Elemtype e){
    if(i<0||i>L->length) return ERROR;
    PLNode pnode = L->headnode;
    PLNode pnode_pre = NULL;
    while(pnode&&i) pnode_pre = pnode, pnode = pnode->next, --i;
    if(pnode==NULL) return ERROR;
    PLNode newnode = NULL;
    if(ERROR == CreateNode_Lk(e, newnode)) return ERROR;
    pnode_pre->next = newnode;
    newnode->next = pnode;
    ++L->length;
    return OK;
}

Status ListDelete_Lk(LinkList* L, int i, Elemtype* e){
    if(i<0||i>L->length) return ERROR;
    PLNode pnode = L->headnode;
    PLNode pnode_pre = NULL;
    while(pnode&&i) pnode_pre = pnode, pnode = pnode->next, --i;
    if(pnode==NULL) return ERROR;
    *e = pnode->data;
    PLNode deletenode = pnode;
    pnode_pre->next = pnode->next;
    free(deletenode);
    ++L->length;
    return OK;
}
