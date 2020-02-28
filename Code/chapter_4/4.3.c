//堆排序
#include <stdio.h>

typedef int ElementType;

void Swap(ElementType *a, ElementType *b)
{
    ElementType t = *a;
    *a = *b;
    *b = t;
}

//改边堆代码中的PerDown(MaxHeap H, int P)函数
//将N个元素的数组中以A[P]为根的子堆调整为最大堆
void PerDown(ElementType A[], int p, int N)
{
    int Parent, Child;
    ElementType X;

    //取出根节点存放的值
    X = A[p];
    for (Parent = p; (Parent * 2 + 1) < N; Parent = Child)
    {
        Child = Parent * 2 + 1;
        //Child指向左右子节点的较大值
        if ((Child != N - 1) && (A[Child] < A[Child + 1]))
            Child++;
        //找到了合适的位置
        if (X >= A[Child])
            break;
        //下滤
        else
            A[Parent] = A[Child];
    }
    A[Parent] = X;
}

//堆排序
void Heap_Sort(ElementType A[], int N)
{
    int i;

    //建立最大堆
    for (i = N / 2 - 1; i >= 0; i--)
        PerDown(A, i, N);

    //删除最大堆项
    for (i = N - 1; i > 0; i--)
    {
        Swap(&A[0], &A[i]);
        PerDown(A, 0, i);
    }
}
