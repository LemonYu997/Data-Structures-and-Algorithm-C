//二叉搜索树
#include <stdio.h>
#include <stdlib.h>

//链表存储
#define ElementType int

typedef struct TreeNode *BinTree;
typedef BinTree Position;
struct TreeNode {
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

//查找操作
//尾递归实现
Position Find(ElementType X, BinTree BST)
{
    if (!BST)
        return NULL;
    if (X > BST->Data)
        return Find(X, BST->Right);     //在右子树中继续查找
    else if (X < BST->Data)
        return Find(X, BST->Left);      //在左子树中继续查找
    else        //X == BST->Data
        return BST;
}

//迭代实现
Position IterFind(ElementType X, BinTree BST)
{
    while(BST)
    {
        if (X > BST->Data)
            BST = BST->Right;           //向右子树移动，继续查找
        else if (X < BST->Data)
            BST = BST->Left;            //向左子树移动，继续查找
        else                            //X == BST->Data
            return BST; //查找成功
    }
    return NULL;        //查找失败
}


//递归查找最小元素
Position FindMin(BinTree BST)
{
    if (!BST)
        return NULL;                //空树
    else if (!BST->Left)
        return BST;                 //最小元素在最左子树
    else
        return FindMin(BST->Left);  //沿左分支继续查找
}

//迭代查找最大元素
Position FindMax(BinTree BST)
{
    if (BST)
        while(BST->Right)
            BST = BST->Right;       //最大值在最右子树

    return BST;
}


//插入
BinTree Insert(ElementType X, BinTree BST)
{   
    //若原树为空，生成并返回一个节点的二叉搜索树
    if (!BST)
    {
        BST = malloc(sizeof(struct TreeNode));
        BST->Data = X;
        BST->Left = BST->Right = NULL;
    }
    else if (X < BST->Data)
        BST->Left = Insert(X, BST->Left);       //递归插入左子树
    else if (X > BST->Data)
        BST->Right = Insert(X, BST->Right);     //递归插入右子树

    //X已存在
    return BST;
}



//删除操作
BinTree Delete(ElementType X, BinTree BST)
{
    Position Tmp;

    if (!BST)
        printf("Not Found this Element");
    else if (X < BST->Data)
        BST->Left = Delete(X, BST->Left);       //左子树递归删除
    else if (X > BST->Data)
        BST->Right = Delete(X, BST->Right);     //右子树递归删除
    //被删除的节点有左右两个子节点
    else if (BST->Left && BST->Right)                     
    {
        Tmp = FindMin(BST->Right);
        BST->Data = Tmp->Data;                          //在右子树中找最小的元素填充删除节点
        BST->Right = Delete(BST->Data, BST->Right);     //在删除节点的右子树中删除最小元素
    }
    //被删除节点有一个或没有子节点
    else
    { 
        Tmp = BST;
        if (!BST->Left)         //有右孩子或无子节点
            BST = BST->Right;
        else if (!BST->Right)   //有左孩子或无子节点
            BST = BST->Left;        
        free(Tmp);
    }
    return BST;
}