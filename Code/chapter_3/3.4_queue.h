//队列的顺村存储实现
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElementType;
#define MaxSize 255
#define ERROR -255

struct QNode{
    ElementType Data[MaxSize];
    int rear;
    int front;
};
typedef struct QNode *Queue;

Queue CreateQueue()
{
    Queue Q = (Queue)malloc(sizeof(struct QNode));
    Q->front = Q->rear = 0;
    return Q;
}

bool IsFull(Queue Q)
{
    return ((Q->rear + 1) % MaxSize == Q->front);
}

bool AddQ(Queue Q, ElementType X)
{
    if (IsFull(Q))
    {
        printf("队列满了");
        return false;
    }
    else
    {
        Q->rear = (Q->rear + 1) % MaxSize;
        Q->Data[Q->rear] = X;
        return true;
    }
}

bool IsEmpty(Queue Q)
{
    return (Q->front == Q->rear);
}

ElementType DeleteQ(Queue Q)
{
    if (IsEmpty(Q))
    {
        printf("队列空");
        return ERROR;
    }
    else
    {
        Q->front = (Q->front + 1) % MaxSize;
        return Q->Data[Q->front];
    }
}