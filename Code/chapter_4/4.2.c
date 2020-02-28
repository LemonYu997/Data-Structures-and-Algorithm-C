//希尔排序-用Sedgewick增量序列
#include <stdio.h>

typedef int ElementType;

//希尔排序
void Bubble_Sort(ElementType A[], int N)
{
    int Si, D, P, i;
    ElementType Tmp;

    //这里只列出一小部分增量
    int Sedgewick[] = {929, 505, 209, 109, 41, 19, 5, 1, 0};

    //初始的增量Sedgewick[Si]不能超过待排序长度
    for (Si = 0; Sedgewick[Si] > N; Si++)
        ;

    for (D = Sedgewick[Si]; D > 0; D = Sedgewick[++Si])
    {   
        //插入排序
        for (P = D; P < N; P++)
        {
            Tmp = A[P];
            for (i = P; i >= D && A[i - D] > Tmp; i -= D)
                A[i] = A[i - D];
            A[i] = Tmp;
        }
    }
}

