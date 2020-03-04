//线性表的链式存储实现
#include <stdio.h>
#include <stdlib.h>

#ifndef _List_H_

typedef int ElementType;
struct LNode;
typedef struct LNode *List;
List Ptrl;

int Length(List Ptrl);
List FindKth(int K, List Ptrl);
List Find(ElementType X, List Ptrl);
List Insert(ElementType X, int i, List Ptrl);
List Delete(int i, List Ptrl);

#endif

typedef struct LNode *List;
struct LNode{
    ElementType Data;
    List Next;
};
struct LNode L;

//求表长
int Length(List Ptrl)
{
    List p = Ptrl;
    int j = 0;
    while (p)
    {
        p = p->Next;
        j++;
    }
    return j;
}

//查找
//按序号查找：FindKth
List FindKth(int K, List Ptrl)
{
    List p = Ptrl;
    int i = 1;
    while (p != NULL && i < K)
    {
        p = p->Next;
        i++;
    }
    if(i == K)
        return p;
    else
        return NULL;
}

//按值查找
List Find(ElementType X, List Ptrl)
{
    List p = Ptrl;
    while(p != NULL && p->Data != X)
        p = p->Next;
    return p;
}

//插入
List Insert(ElementType X, int i, List Ptrl)
{
    List p, s;
    if(i == 1)
    {
        s = (List)malloc(sizeof(struct LNode));
        s->Data = X;
        s->Next = Ptrl;
        return s;
    }
    p = FindKth(i - 1, Ptrl);
    if (p == NULL)
    {
        printf("参数i错误");
        return NULL;
    }
    else
    {
        s = (List)malloc(sizeof(struct LNode));
        s->Data = X;
        s->Next = p->Next;
        p->Next = s;
        return Ptrl;
    }
}

//删除
List Delete(int i, List Ptrl)
{
    List p, s;
    if (i == 1)
    {
        s = Ptrl;
        if (Ptrl != NULL)
            Ptrl = Ptrl->Next;
        else
            return NULL;
        free(s);
        return Ptrl;
    }
    p = FindKth(i - 1, Ptrl);
    if ( p == NULL)
    {
        printf("第%d个结点不存在", i - 1);
        return NULL;
    }else if(p->Next == NULL)
    {
        printf("第%d个结点不存在", i);
        return NULL;
    }else
    {
        s = p->Next;
        p->Next = s->Next;
        free(s);
        return Ptrl;
    }
}