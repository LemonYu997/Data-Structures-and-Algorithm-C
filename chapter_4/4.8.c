//基数排序-主位优先 MSD
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

//假设元素最多右MaxDigit个关键字，基数全是同样的Radix
#define MaxDigit 4
#define Radix 10

//桶元素结点
typedef struct Node *PtrToNode;
struct Node {
    int Key;
    PtrToNode next;
};

//桶头节点
struct HeadNode {
    PtrToNode head, tail;
};
typedef struct HeadNode Bucket[Radix];

//默认次位D = 1,诸位 D <= MaxDigit
int GetDigit(int X, int D)
{
    int d, i;

    for (i = 1; i <= D; i++)
    {
        d = X % Radix;
        X /= Radix;
    }
    return d;
}

//基数排序，次位优先
void MSD(ElementType A[], int L, int R, int D)
{
    int Di, i, j;
    Bucket B;
    PtrToNode tmp, p, List = NULL;

    //递归终止条件
    if (D == 0)
        return;

    //初始化每个桶为空链表
    for (i = 0; i < Radix; i++)
        B[i].head = B[i].tail = NULL;
    //将原始序列逆序存入初始链表List
    for (i = L; i <= R; i++)
    {
        tmp = (PtrToNode)malloc(sizeof(struct Node));
        tmp->Key = A[i];
        tmp->next = List;
        List = tmp;
    }
    //下面是分配的过程
    p = List;
    while (p)
    {
        //获得当前元素的当前位数字
        Di = GetDigit(p->Key, D);
        //从List中摘除
        tmp = p;
        p = p->next;
        //插入B[Di]号桶
        if (B[Di].head == NULL)
            B[Di].tail = tmp;
        tmp->next = B[Di].head;
        B[Di].head = tmp;
    }
    //下面是收集的过程
    i = j = L;      //i, j记录当前要处理的A[]的左右端下标
    //对于每个桶
    for (Di = 0; Di < Radix; Di++)
    {
        //将非空的桶整数倒入A[]，递归排序
        if (B[Di].head)
        {
            p = B[Di].head;
            while (p)
            {
                tmp = p;
                p = p->next;
                A[j++] = tmp->Key;
                free(tmp);
            }
            //递归对该桶数据排序，位序-1
            MSD(A, i, j - 1, D - 1);
            //为下一个桶对应的A[]左端
            i = j;
        }
    }
}

//统一接口
void MSDRadixSort(ElementType A[], int N)
{
    MSD(A, 0, N - 1, MaxDigit);
}