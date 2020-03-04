//快速排序
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

void Swap(ElementType *a, ElementType *b)
{
    ElementType t = *a;
    *a = *b;
    *b = t;
}

//插入排序
void Insert_Sort(ElementType A[], int N)
{
    int P, i;
    ElementType Tmp;

    for (P = 1; P < N; P++)
    {   
        //取出未排序序列中的第一个元素
        Tmp = A[P];
        //依次与已排序序列中的元素比较并右移
        for (i = P; i > 0 && A[i - 1] > Tmp; i--)
            A[i] = A[i - 1];
        //放进合适的位置
        A[i] = Tmp;
    }
}

ElementType Median3(ElementType A[], int Left, int Right)
{
    int Center = (Left + Right) / 2;
    if (A[Left] > A[Center])
        Swap(&A[Left], &A[Center]);
    if (A[Left] < A[Right])
        Swap(&A[Left], &A[Right]);
    if (A[Center] > A[Right])
        Swap(&A[Center], &A[Right]);
    //此时A[left] <= A[Center] <= A[Right]
    Swap(&A[Center], &A[Right - 1]);        //将基准Pivot藏到右边
    //只需要考虑A[Left + 1] ... A[Right - 2]
    return A[Right - 1];                    //返回基准Pivot
}

//核心递归函数
void Qsort(ElementType A[], int Left, int Right)
{
    int Pivot, Cutoff, Low, High;

    //只有数量大的时候，用快速排序效率才比较高
    //Cutoff是一个阈值，小于这个数的排序用插入
    Cutoff = 10000;                 

    //如果序列元素充分多，进入快排
    if (Cutoff <= Right - Left)
    {
        Pivot = Median3(A, Left, Right);    //选基准
        Low = Left;
        High = Right - 1;
        //将序列中基准小的移到基准左边，大的移到右边
        while (1)
        {
            while (A[++Low] < Pivot)
                ;
            while (A[--High] > Pivot)
                ;
            if (Low < High)
                Swap(&A[Low], &A[High]);
            else
                break;
        }
        Swap(&A[Low], &A[Right - 1]);       //将基准换到正确的位置
        Qsort(A, Left, Low - 1);            //递归解决左边
        Qsort(A, Low + 1, Right);           //递归解决右边
    }
    //元素太少，用简单排序
    else
        Insert_Sort(A + Left, Right - Left + 1);
}

//统一接口
void QuickSort(ElementType A[], int N)
{
    Qsort(A, 0, N - 1);
}