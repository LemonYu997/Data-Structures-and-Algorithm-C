//集合 
#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000                   //集合最大元素个数
typedef int ElementType;            //默认元素可以用非负整数表示
typedef int SetName;                //默认用根节点的下标作为集合名称
typedef ElementType SetType[MAXN];  //假设集合元素下标从0开始

//集合的并运算
void Union(SetType S, SetName Root1, SetName Root2)
{  
    //默认Root1和Root2是不同集合的根节点
    //保证小集合并入大集合
    //如果集合2比较大，集合1并入集合2
    if (S[Root1] < S[Root2])
    {
        S[Root2] += S[Root1];
        S[Root1] = Root2;
    }
    //如果集合1比较大，集合2并入集合1
    else
    {
        S[Root1] += S[Root2];
        S[Root2] = Root1;
    }
}

//查找元素 X 是否在集合中
SetName Find(SetType S, ElementType X)
{
    //默认集合元素全部初始化为-1
    //找到集合的根
    if (S[X] < 0)
        return X;
    //路径压缩
    else
        return S[X] = Find(S, S[X]);
}