//平衡二叉树
#include <stdio.h>
#include <stdlib.h>

//链表存储
#define ElementType int

typedef struct AVLNode *Position;
typedef Position AVLTree;
struct AVLNode {
    ElementType Data;
    AVLTree Left;
    AVLTree Right;
    int Height;         //树高
};


int Max(int a, int b)
{
    return a > b ? a : b;
}

//求树高
int GetHeight(AVLTree A)
{
    int HL, HR, MaxH;
    if (A)
    {   
        //求左子树高度
        HL = GetHeight(A->Left);
        //求右子树高度
        HR = GetHeight(A->Right);
        //取最大
        MaxH = (HL > HR) ? HL : HR;
        //结果加1（加上根的的高度）
        return (MaxH + 1);
    }
    else
        return 0;
}


//左单旋
AVLTree SingleLeftRotation(AVLTree A)
{
    //A必须有一个左子节点B
    //将A与B做左单旋，更新A与B的高度，返回新的根节点B

    AVLTree B = A->Left;
    A->Left = B->Right;
    B->Right = A;

    A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
    B->Height = Max(GetHeight(B->Left), A->Height) + 1;

    return B;
}

//右单旋
AVLTree SingleRightRotation(AVLTree A)
{
    //A必须有一个右子节点B
    //将A与B做右单旋，更新A与B的高度，返回新的根节点B

    AVLTree B = A->Right;
    A->Right = B->Left;
    B->Left = A;

    A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
    B->Height = Max(GetHeight(B->Left), A->Height) + 1;

    return B;
}

//左右双旋
AVLTree DoubleLeftRightRotation(AVLTree A)
{
    //A必须有一个左子节点B，B必须有一个右子节点C
    //将A、B和C做两次单旋，并返回新的根节点C

    //将B与C做右单旋，C被返回
    A->Left = SingleRightRotation(A->Left);
    //将A与C做左单旋，C被返回
    return SingleLeftRotation(A);
}

//右左双旋
AVLTree DoubleRightLeftRotation(AVLTree A)
{
    //A必须有一个右子节点B，B必须有一个左子节点C
    //将A、B和C做两次单旋，并返回新的根节点C

    //将B与C做左单旋，C被返回
    A->Left = SingleLeftRotation(A->Right);
    //将A与C做右单旋，C被返回
    return SingleRightRotation(A);
}



//插入
AVLTree Insert(AVLTree T, ElementType X)
{
    //将X插入AVL树T中，并返回调整后的AVL树
    if (!T)
    {
        //若插入空树，则新建包含一个节点的树
        T = (AVLTree)malloc(sizeof(struct AVLNode));
        T->Data = X;
        T->Height = 0;
        T->Left = T->Right = NULL;
    }
    else if (X < T->Data)
    {
        //插入T的左子树
        T->Left = Insert(T->Left, X);
        //如果需要左旋
        if (GetHeight(T->Left) - GetHeight(T->Right) == 2)
        {
            if (X < T->Left->Data)
                T = SingleLeftRotation(T);      //左单旋
            else
                T = DoubleLeftRightRotation(T); //左右双旋
        }
    }
    else if (X > T->Data)
    {
        //插入T的右子树
        T->Right = Insert(T->Right, X);
        //如果需要右旋
        if (GetHeight(T->Left) - GetHeight(T->Right) == 2)
        {
            if (X > T->Right->Data)
                T = SingleRightRotation(T);     //右单旋
            else
                T = DoubleRightLeftRotation(T); //右左双旋
        }

        //else X == T->Data，无须插入

        //更新树高
        T->Height = Max(GetHeight(T->Left), GetHeight(T->Right) + 1);
    }

    return T;
}