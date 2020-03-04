//构造哈夫曼树
//注：最小堆 MinHeap 的相关函数见 2.5.c，只需做修改将最大改为最小，并在节点中加入 Weight（权重）元素
#include <stdio.h>
#include <stdlib.h>

//定义
typedef struct TreeNode *HuffmanTree;

struct TreeNode {
    int Weight;
    HuffmanTree Left, Right;
};

//构建哈夫曼树，假设H->Size个权值已经存在H->Data[]->Weight中
HuffmanTree Huffman(MinHeap H)
{
    int i;
    HuffmanTree T;
    //将H->Data[]按权值调整为最小堆
    BuildMinHeap(H);
    //做H->Size - 1次合并
    for (i = 1; i < H->Size; i++)
    {
        //建立新节点
        T = malloc(sizeof(struct TreeNode));
        //从最小堆中删除一个节点，作为新T的左子节点
        T->Left = DeleteMin(H);
        //从最小堆中删除一个节点，作为新T的右子节点
        T->Right = DeleteMin(H);
        //计算新权值
        T->Weight = T->Left->Weight + T->Right->Weight;
        //将新T插入最小堆
        Insert(H, T);
    }
    T = DeleteMin(H);
    return T;
}