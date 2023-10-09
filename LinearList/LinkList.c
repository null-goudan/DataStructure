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
}LNode, *LinkList;

void DeleteX_2(LinkList L, Elemtype x){
    LNode *p, *r, *q;
    p = L->next;    //指向第一个元素
    r = L;  //作为新表的表尾
    L->next = NULL; // 将头部断开
    while(p != NULL){
        if(p->data != x){
            r->next = p; // 尾部插入法
            r = p;          // 更新尾部
            p = p->next;
        }else if(p ->data == x){    // 释放空间 
            q = p;
            p = p->next;
            free(q);
        }
    }

}
