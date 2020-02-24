//最短路径算法， Dijkstra算法
//邻接矩阵存储——有权图的单源最短路径算法
//使用到了邻接矩阵相关头文件
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "3.4_M.h"

#define ERROR -9999

//返回未被收录顶点种dist最小者
Vertex FindMinDist(MGraph Graph, int dist[], int collected[])
{
    Vertex MinV, V;
    int MinDist = INFINITY;

    for (V = 0; V < Graph->Nv; V++)
    {   
        //若V未被收录，且dist[V]更小
        if (collected[V] == false && dist[V] < MinDist)
        {
            MinDist = dist[V];          //更新最小距离
            MinV = V;                   //更新对应顶点
        }
    }
    //若找到最小dist
    if (MinDist < INFINITY)
        return MinV;                    //返回对应的顶点下标
    //若这样的顶点不存在，返回错误标记
    else
        return ERROR;
}

bool Dijkstra(MGraph Graph, int dist[], int path[], Vertex S)
{
    int collected[MaxVertexNum];
    Vertex V, W;

    //初始化：此处默认邻接矩阵中不存在的边用INFINTY表示
    for (V = 0; V < Graph->Nv; V++)
    {
        dist[V] = Graph->G[S][V];
        if (dist[V] < INFINITY)
            path[V] = S;
        else
            path[V] = -1;
        collected[V] = false;
    }
    //先将起点收入集合
    dist[S] = 0;
    collected[S] = true;

    while (1)
    {
        //V = 未被收录顶点中dist最小者
        V = FindMinDist(Graph, dist, collected);
        //若这样的 V 不存在
        if (V == ERROR)
            break;                  //算法结束
        collected[V] = true;        //收录 V
        //对图中的每个顶点W
        for (W = 0; W < Graph->Nv; W++)
        {
            //若W是V的邻接点并且未被收录
            if (collected[W] == false && Graph->G[V][W] < INFINITY)
            {
                //若有负边
                if (Graph->G[V][W] < 0)
                    return false;   //不能正确解决，返回错误标记
                //若收录V使得dist[W]变小
                if (dist[V] + Graph->G[V][W] < dist[W])
                {   
                    //更新dist[W]
                    dist[W] = dist[V] + Graph->G[V][W];
                    //更新S到W的路径
                    path[W] = V;
                }
            }
        }
    }
    //算法执行完毕，返回正确标记
    return true;
}