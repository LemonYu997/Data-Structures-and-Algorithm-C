//栈的顺序存储实现
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef _Stack_H_

typedef int ElementType;
#define MaxSize 255
#define ERROR -255
struct SNode{
    ElementType *Data;          //存储元素的数组
    int Top;
};
typedef struct SNode *Stack;

#endif

Stack CreateStack()
{
    Stack S = (Stack)malloc(sizeof(struct SNode));
    S->Data = (ElementType *)malloc(MaxSize * sizeof(ElementType));
    S->Top = -1;
    return S;
}

bool IsFull(Stack S)
{
    return (S->Top == MaxSize - 1);
}

bool Push(Stack S, ElementType X)
{
    if (IsFull(S))
    {
        printf("栈满了");
        return false;
    }
    else
    {
        S->Data[++(S->Top)] = X;
        return true;
    }
}

bool IsEmpty(Stack S)
{
    return (S->Top == -1);
}

ElementType Pop(Stack S)
{
    if (IsEmpty(S))
    {
        printf("栈空了");
        return ERROR;           //一个表示错误的数值，自定
    }
    else
        return (S->Data[(S->Top)--]);
}