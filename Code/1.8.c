//栈的链式存储实现
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef _Stack_H_

typedef int ElementType;
#define MaxSize 255
#define ERROR -255

struct SNode{
    ElementType Data;          //存储元素的数组
    struct SNode *Next;
};
typedef struct SNode *PtrToSNode;
typedef PtrToSNode Stack;

#endif

Stack CreateStack()
{
    Stack S;
    S = (Stack)malloc(sizeof(struct SNode));
    S->Next = NULL;
    return S;
}

bool IsEmpty(Stack S)
{
    return (S->Next == NULL);
}

bool Push(Stack S, ElementType X)
{
    PtrToSNode TmpCell;

    TmpCell = (PtrToSNode)malloc(sizeof(struct SNode));
    TmpCell->Data = X;
    TmpCell->Next = S->Next;
    S->Next = TmpCell;
    return true;
}

ElementType Pop(Stack S)
{
    PtrToSNode FirstCell;
    ElementType TopElem;

    if (IsEmpty(S))
    {
        printf("栈空");
        return ERROR;
    }
    else
    {
        FirstCell = S->Next;
        TopElem = FirstCell->Data;
        S->Next = FirstCell->Next;
        free(FirstCell);
        return TopElem;
    }
}