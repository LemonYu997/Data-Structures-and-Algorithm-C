//简单排序（冒泡、插入排序）
#include <stdio.h>

typedef int ElementType;

//冒泡排序
void Bubble_Sort(ElementType A[], int N)
{
    int P, i, flag;
    ElementType Tmp;

    //倒着冒泡
    for (P = N - 1; P >= 0; P--)
    {
        flag = 0;
        //一趟冒泡
        for (i = 0; i < P; i++)
        {   
            //比较相邻的两个数，把小的放在大的前边
            if (A[i] > A[i+1])
            {
                Tmp = A[i];
                A[i] = A[i + 1];
                A[i + 1] = Tmp;
                flag = 1;       //标识符发生了交换
            }
        }
        //全程无交换
        if (flag == 0)
            break;
    }
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