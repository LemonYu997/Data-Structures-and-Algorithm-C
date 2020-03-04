//一个数组存放两个栈
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef _Stack_H_

typedef int ElementType;
#define MaxSize 255

struct DStack{
    ElementType Data[MaxSize];          //存储元素的数组
    int Top1;
    int Top2;
};
typedef struct DStack *Stack;

#endif

Stack CreateStack()
{
    Stack S = (Stack)malloc(sizeof(struct DStack));
    S->Top1 = -1;
    S->Top2 = MaxSize;
    return S;
}



void Push(struct DStack *PtrS, ElementType item, int Tag)
{
    if (PtrS->Top2 - PtrS->Top1 == 1)
    {
        printf("栈满了");
        return;
    }
    if (Tag == 1)
        PtrS->Data[++(PtrS->Top1)] = item;
    else
        PtrS->Data[--(PtrS->Top2)] = item;
}

ElementType Pop(struct DStack *PtrS, int Tag)
{
    if (Tag == 1)
    {
        if (PtrS->Top1 == -1)
        {
            printf("栈1空");
            return (int)NULL;                       //直接NULL的化格式和ElementType 格式不对应
        }
        else
            return PtrS->Data[(PtrS->Top1)--];
    }
    else
    {
        if (PtrS->Top2 == MaxSize)
        {
            printf("栈2空");
            return (int)NULL;
        }
        else
            return PtrS->Data[(PtrS->Top2)++];
    }
}