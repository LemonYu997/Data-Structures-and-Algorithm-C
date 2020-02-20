//堆 最大堆 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//数组实现
#define ElementType int

typedef struct HNode *Heap;         //堆的类型定义

struct HNode {
    ElementType *Data;              //存储元素的数组
    int Size;                       //堆中当前元素个数
    int Capacity;                   //堆的最大容量
};

typedef Heap MaxHeap;               //最大堆
typedef Heap MinHeap;               //最小堆

//设置一个标兵，其值应大于堆中所有可能元素的值
#define MAXDATA 1000               

//创建一个空的最大堆
MaxHeap CreateHeap(int MaxSize)
{   
    //分配空间
    MaxHeap H = (MaxHeap)malloc(sizeof(struct HNode));
    H->Data = (ElementType *)malloc((MaxSize + 1) * sizeof(ElementType));
    H->Size = 0;
    H->Capacity = MaxSize;
    H->Data[0] = MAXDATA;           //定义标兵，为最顶元素

    return H;
}

//判断堆是否已满
bool IsFull(MaxHeap H)
{
    //容量到达最大值即满
    return (H->Size == H->Capacity);
}

//将元素 X 插入堆 H 中，其中Data[0]已设为标兵
bool Insert(MaxHeap H, ElementType X)
{   
    int i;

    if (IsFull(H))
    {
        printf("Heap is full\n");
        return false;
    }
    i = ++H->Size;                  // i 指向插入后堆中的最后一个元素的位置
    //向上过滤
    for (; H->Data[i / 2] < X; i /= 2)
        H->Data[i] = H->Data[i / 2];
    //将X插入
    H->Data[i] = X;

    return true;
}

//定义错误标识，应为堆中不可能出现的元素值
#define ERROR -1

//判断堆是否为空
bool IsEmpty(MaxHeap H)
{
    return (H->Size == 0);
}

//从最大堆 H 中取出值最大的一个元素，并删除该节点
ElementType DeleteMax(MaxHeap H)
{
    int Parent, Child;                  //数组节点下标
    ElementType MaxItem, X;

    if (IsEmpty(H))
    {
        printf("Heap is full\n");
        return ERROR;
    }

    //取出根节点的值即最大值
    MaxItem = H->Data[1];
    //用最大堆中最后一个元素 X 从根节点开始过滤下层节点
    X = H->Data[H->Size--];             //注意当前堆的规模要减小
    for (Parent = 1; Parent * 2 <= H->Size; Parent = Child)
    {
        Child = Parent * 2;
        //Child指向左右子节点的较大值
        if ((Child != H->Size) && (H->Data[Child] < H->Data[Child + 1]))
            Child++;                   
        //找到了合适的位置时
        if (X > H->Data[Child])
            break;
        //下滤
        else
            H->Data[Parent] = H->Data[Child];
    }
    //此时的节点即为 X 挪入的位置
    H->Data[Parent] = X;

    return MaxItem;
}

//建造最大堆
//下滤：将 H 中以 H->Data[p]为根的子堆调整为最大堆
void PercDown(MaxHeap H,int p)
{
    int Parent, Child;
    ElementType X;

    //取出根节点存放的值
    X = H->Data[p];
    for (Parent = p; Parent * 2 <= H->Size; Parent = Child)
    {
        Child = Parent * 2;
        //Child指向左右子节点的较大值
        if ((Child != H->Size) && (H->Data[Child] < H->Data[Child + 1]))
            Child++;                   
        //找到了合适的位置时
        if (X > H->Data[Child])
            break;
        //下滤
        else
            H->Data[Parent] = H->Data[Child];
    }
    //此时的节点即为 X 挪入的位置
    H->Data[Parent] = X;
}

//调整 H->Data[] 中的所有元素，使其满足最大堆的有序性，这里假设所有 H->Size 个元素已经存在 H->Data[] 中
void BuildHeap(MaxHeap H)
{
    int i;

    //从最后一个节点的父节点开始，到根节点1
    for (i = H->Size / 2; i > 0; i--)
    {
        PercDown(H, i);
    }
}