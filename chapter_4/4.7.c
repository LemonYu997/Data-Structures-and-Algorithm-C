//基数排序-次位优先 LSD
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
void LSDRadixSort(ElementType A[], int N)
{
    int D, Di, i;
    Bucket B;
    PtrToNode tmp, p, List = NULL;

    //初始化每个桶为空链表
    for (i = 0; i < Radix; i++)
        B[i].head = B[i].tail = NULL;
    //将原始序列逆序存入初始链表List
    for (i = 0; i < N; i++)
    {
        tmp = (PtrToNode)malloc(sizeof(struct Node));
        tmp->Key = A[i];
        tmp->next = List;
        List = tmp;
    }

    //开始排序
    //对数据的每一位循环处理
    for (D = 1; D <= MaxDigit; D++)
    {
        //分配
        p = List;
        while (p)
        {
            //获得当前元素的当前位数字
            Di = GetDigit(p->Key, D);
            //从List中摘除
            tmp = p;
            p = p->next;
            //插入B[Di]号桶尾
            tmp->next = NULL;
            if (B[Di].head == NULL)
                B[Di].head = B[Di].tail = tmp;
            else
            {
                B[Di].tail->next = tmp;
                B[Di].tail = tmp;
            }
        }
        //下面是收集的过程
        List = NULL;
        //将每个桶的元素顺序收集入List
        for (Di = Radix - 1; Di >= 0; Di--)
        {
            //如果桶不为空
            if (B[Di].head)
            {
                //整桶插入List表头
                B[Di].tail->next = List;
                List = B[Di].head;
                B[Di].head = B[Di].tail = NULL; //清空桶
            }
        }
        //将List倒入A[]并释放空间
        for (i = 0; i < N; i++)
        {
            tmp = List;
            List = List->next;
            A[i] = tmp->Key;
            free(tmp);
        }
    }
}