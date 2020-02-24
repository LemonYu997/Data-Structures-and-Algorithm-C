//最短路径算法
//邻接表存储——无权图的单源最短路径算法
//使用到了队列、邻接表相关头文件
#include <stdio.h>
#include <stdlib.h>
#include "3.3_Adj.h"
#include "3.4_queue.h"

//dist[]和path[]全部初始化为-1
void Unweighted(LGraph Graph, int dist[], int path[], Vertex S)
{
    Queue Q;
    Vertex V;
    PtrToAdjVNode W;

    //创建空队列
    Q = CreateQueue();
    dist[S] = 0;                    //初始化源点
    AddQ(Q, S);

    while (!IsEmpty(Q)) 
    {
        V = DeleteQ(Q);
        //对V的每个邻接点W->AdjV
        for (W = Graph->G[V].FirstEdge; W; W = W->Next)
        {   
            //如果 W->AdjV 未被访问过
            if (dist[W->AdjV] == -1)
            {   
                //W->AdjV到S的距离更新
                dist[W->AdjV] = dist[V] + 1;
                //将V记录在S到W->AdjV的路径上
                path[W->AdjV] = V;
                AddQ(Q, W->AdjV);
            }
        }
    }
}
