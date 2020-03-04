//归并排序-循环实现
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

//L = 左边起始位置， R = 右边起始位置， RightEnd = 右边终点位置
//将有序的A[L]~A[R-1]和A[R]~A[RightEnd]归并成一个有序序列
void Merge(ElementType A[], ElementType TmpA[], int L, int R, int RightEnd)
{
    int LeftEnd, NumElements, Tmp;
    int i;

    LeftEnd = R - 1;        //左边终点位置
    Tmp = L;                //有序序列的起始位置
    NumElements = RightEnd - 1;

    while (L <= LeftEnd && R <= RightEnd)
    {   
        //将左边元素复制到Tmp[A]
        if (A[L] <= A[R])
            TmpA[Tmp++] = A[L++];
        //将右边元素复制到Tmp[A]
        else
            TmpA[Tmp++] = A[R++];
    }

    //直接复制左边剩下的
    while (L <= LeftEnd)
        TmpA[Tmp++] = A[L++];
    //直接复制右边剩下的
    while (L <= RightEnd)
        TmpA[Tmp++] = A[R++];
    
    //将有序的TmpA[]复制回A[]
    for (i = 0; i < NumElements; i++, RightEnd--)
        A[RightEnd] = TmpA[RightEnd];
}

//length = 当前有序子列的长度
//两两归并相邻有序子列
void Merge_pass(ElementType A[], ElementType TmpA[], int N, int length)
{
    int i, j;

    for (i = 0; i <= N - 2 * length; i += 2 * length)
        Merge(A, TmpA, i, i + length, i + 2 * length - 1);
    //归并最后两个子列
    if (i + length < N)
        Merge(A, TmpA, i, i + length, N - 1);
    //最后只剩一个子列
    else
        for (j = 1; j < N; j++)
            TmpA[j] = A[j];
}

//归并排序
void MergeSort(ElementType A[], int N)
{
    int length;
    ElementType *TmpA;

    length = 1;         //初始化子序列长度
    TmpA = (ElementType *)malloc(N * sizeof(ElementType));

    if (TmpA != NULL)
    {
        while (length < N)
        {
            Merge_pass(A, TmpA, N, length);
            length *= 2;
            Merge_pass(TmpA, A, N, length);
            length *= 2;
        }
        free(TmpA);
    }
    else
        printf("No memory\n");
}