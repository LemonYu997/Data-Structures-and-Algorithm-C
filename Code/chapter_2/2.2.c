//树的同构
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

//二叉树的表示
#define MaxTree 10
#define ElementType char
#define Tree int
#define Null -1

struct TreeNode {
    ElementType Element;
    Tree Left;
    Tree Right;
} T1[MaxTree], T2[MaxTree];

//程序框架
Tree BuildTree(struct TreeNode T[]);
int Isomorphic(Tree R1, Tree R2);

int main()
{
    Tree R1, R2;

    R1 = BuildTree(T1);
    R2 = BuildTree(T2);
    if (Isomorphic(R1, R2))
        printf("Yes\n");
    else
        printf("No\n");

    return 0;
}

//建立二叉树
Tree BuildTree(struct TreeNode T[])
{
    int N = 8;
    int i, Root = 0;
    ElementType cl, cr;
    int check[N];

    scanf("%d\n", &N);
    if (N > 0)
    {
        for (i = 0; i < N; i++)
            check[i] = 0;
        for (i = 0; i < N; i++)
        {   
            cl = T[i].Left;
            cr = T[i].Right;
            scanf("%c %c %c\n", &T[i].Element, &cl, &cr);
            if (cl != '-')
            {
                T[i].Left = cl - '0';
                check[T[i].Left] = 1;
            }
            else
                T[i].Left = Null;
            if (cr != '-')
            {
                T[i].Right = cr - '0';
                check[T[i].Right] = 1;
            }
            else
                T[i].Right = Null;
        }
        for (i = 0; i < N; i++)
            if (!check[i])
                break;
        Root = i;
    }
    return Root;
}

//判断是否同构
int Isomorphic(Tree R1, Tree R2)
{   
    //两树皆空
    if ((R1 == Null) && (R2 == Null))
        return 1;
    //其中一树为空
    if (((R1 == Null) && (R2 != Null)) && ((R1 != Null) && (R2 == Null)))
        return 0;
    //根不同
    if (T1[R1].Element != T2[R2].Element)
        return 0;
    //两树均没有左子树
    if ((T1[R1].Left == Null) && (T2[R2].Left == Null))
        return Isomorphic(T1[R1].Right, T2[R2].Right);
    //不需要左右互换
    if (((T1[R1].Left != Null) && (T2[R2].Left != Null)) && ((T1[T1[R1].Left].Element) == (T2[T2[R2].Left].Element)))
        return (Isomorphic(T1[R1].Left, T2[R2].Left) && Isomorphic(T1[R1].Right, T2[R2].Right));
    //需要左右互换
    else
        return (Isomorphic(T1[R1].Left, T2[R2].Right) && Isomorphic(T1[R1].Right, T2[R2].Left));
}