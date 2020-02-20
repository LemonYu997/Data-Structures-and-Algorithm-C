//图——邻接矩阵——广度优先搜索BFS(Breadth First Search)
//图的邻接表形式相关函数见 3.1.c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "3.4_queue.h"              //利用队列的相关函数
#include "3.4_M.h"                  //图的邻接矩阵头文件

// IsEdge(Graph, V, W)检查<V, W>是否图Graph中的一条边，即W是否V的邻接点。 
// 此函数根据图的不同类型要做不同的实现，关键取决于对不存在的边的表示方法。
// 例如对有权图, 如果不存在的边被初始化为INFINITY, 则函数实现如下:
bool IsEdge(MGraph Graph, Vertex V, Vertex W)
{
    return Graph->G[V][W] < INFINITY ? true : false;
}

void Visit(Vertex V)
{
    printf("正在访问顶点%d\n", V);
}

//Visited[]为全局变量，初始化为false
int Visited[MaxVertexNum];
void Initialization(int * Visited[], int Nv)
{
    int i = 0;
    for (i = 0; i < Nv; i++)
        Visited[i] = false;
}

//Visited[]为全局变量，已经初始化为false
//利用队列
//以V为出发点对邻接矩阵存储的图Graph进行BFS搜索
void BFS(MGraph Graph, Vertex S, void (*Visit)(Vertex))
{
    Queue Q;
    Vertex V, W;

    //创建空队列
    Q = CreateQueue();
    //访问顶点S：此处可根据具体访问需要改写
    Visit(S);
    Visited[S] = true;          //标记S已访问
    AddQ(Q, S);                 //S入队列

    while (!IsEmpty(Q))
    {
        V = DeleteQ(Q);         //弹出V
        //遍历途中的每个顶点W
        for (W = 0; W < Graph->Nv;W++)
        {
            //若W是V的邻接点并且未访问过
            if (!Visited[W] && IsEdge(Graph, V, W))
            {
                //访问顶点W
                Visit(W);
                Visited[W] = true;
                AddQ(Q, W);     //W入队列
            }
        }
    }
}
