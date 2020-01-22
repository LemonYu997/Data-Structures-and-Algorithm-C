//线性表的顺序存储实现
#include <stdio.h>
#include <stdlib.h>
//链表类型声明
#ifndef _List_H_

#define MAXSIZE 255
typedef int ElementType;
struct LNode;
typedef struct LNode *List;
List Ptrl;

List MakeEmpty();
int Find(ElementType X, List Ptrl);
void Insert(ElementType X, int i, List Ptrl);
void Delete(int i, List Ptrl);

#endif

struct LNode{
    ElementType Data[MAXSIZE];
    int Last;
};
struct LNode L;

//初始化（建立空的顺序表）
List MakeEmpty()
{
    List Ptrl;
    Ptrl = (List)malloc(sizeof(struct LNode));
    Ptrl->Last = -1;
    return Ptrl;
}

//查找
int Find(ElementType X, List Ptrl)
{
    int i = 0;
    while(i <= Ptrl->Last && Ptrl->Data[i] != X)
        i++;
    if (i > Ptrl->Last)
        return -1;
    else
        return i;
}

//插入
void Insert(ElementType X, int i, List Ptrl)
{
    int j;
    if (Ptrl->Last == MAXSIZE - 1)
    {
        printf("表满了，塞不下");
        return;
    }
    if (i < 1 || Ptrl->Last + 2)
    {
        printf("位置不合法");
        return;
    }
    for (j = Ptrl->Last; j >= i - 1; j--)
        Ptrl->Data[j + 1] = Ptrl->Data[j];
    Ptrl->Data[i - 1] = X;
    Ptrl->Last++;
    return;
}

//删除
void Delete(int i, List Ptrl)
{
    int j;
    if (i < 1 || Ptrl->Last + 1)
    {
        printf("不存在第%d个元素", i);
        return;
    }
    for (j = i; j <= Ptrl->Last; j++)
        Ptrl->Data[j - 1] = Ptrl->Data[j];
    Ptrl->Last--;
    return;
}