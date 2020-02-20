//树的遍历
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

//链表存储
#define ElementType int

typedef struct TreeNode *BinTree;
typedef BinTree Position;
struct TreeNode {
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

//先序遍历
void PreOrderTraversal(BinTree BT)
{
    if (BT)
    {
        printf("%d", BT->Data);
        PreOrderTraversal(BT->Left);
        PreOrderTraversal(BT->Right);
    }
}

//中序遍历
void InOrderTraversal(BinTree BT)
{
    if (BT)
    {
        InOrderTraversal(BT->Left);
        printf("%d", BT->Data);
        InOrderTraversal(BT->Right);
    }
}

//后序遍历
void PostOrderTraversal(BinTree BT)
{
    if (BT)
    {
        PostOrderTraversal(BT->Left);
        PostOrderTraversal(BT->Right);
        printf("%d", BT->Data);
    }
}

//中序遍历的非递归遍历算法
//使用堆栈，相关函数见1.8.c
// void InOrderTraversal_NoRecursion(BinTree BT)
// {
//     BinTree T = BT;
//     //创建并初始化堆栈
//     Stack S = CreatStack(MaxSize);
//     while (T || !IsEmpty(S))
//     {
//         while(T)
//         {
//             Push(S, T);
//             T = T->Left;
//         }
//         if(!IsEmpty(S))
//         {
//             T = Pop(S);
//             printf("%5d", T->Data);
//             T = T->Right;
//         }
//     }
// }

//层序遍历
//使用队列，相关函数详见1.9.c
// void LevelOrderTraversal(BinTree BT)
// {
//     Queue Q;
//     BinTree T;
//     //若为空直接返回
//     if (!BT)
//         return;
//     //创建并初始化队列Q
//     Q = CreateQueue(MaxSize);
//     Add(Q, BT);
//     while(!IsEmptyQ(Q))
//     {
//         T = DeleteQ(Q);
//         //访问并取出队列的节点
//         printf("%d\n", T->Data);
//         if(T->Left)
//             Add(Q, T->Left);
//         if(T->Right)
//             Add(Q, T->Right);
//     }
// }


//例1：输出二叉树中的子节点
void PreOrderPrintLeaves(BinTree BT)
{
    if (BT)
    {   
        //若不存在左子树和右子树就输出
        if (!BT->Left && !BT->Right)
            printf("%d", BT->Data);
        PreOrderPrintLeaves(BT->Left);
        PreOrderPrintLeaves(BT->Right);
    }
}

//例2：求二叉树的高度
int PostOrderGetHeight(BinTree BT)
{
    int HL, HR, MaxH;
    if (BT)
    {   
        //求左子树高度
        HL = PostOrderGetHeight(BT->Left);
        //求右子树高度
        HR = PostOrderGetHeight(BT->Right);
        //取最大
        MaxH = (HL > HR) ? HL : HR;
        //结果加1（加上根的的高度）
        return (MaxH + 1);
    }
    else
        return 0;
}