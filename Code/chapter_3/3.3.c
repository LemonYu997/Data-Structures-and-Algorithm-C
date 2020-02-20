//图——邻接表——深度优先搜索DFS(Depth First Search)
//图的邻接表形式相关函数见 3.2.c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "3.3_Adj.h"                        //图的邻接表头文件

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
//以V为出发点对邻接表存储的图Graph进行DFS搜索
void DFS(LGraph Graph, Vertex V, void (*Visit)(Vertex))
{
    PtrToAdjVNode W;

    Visit(V);                               //访问第V个顶点
    Visited[V] = true;                      //标记V已访问

    //对V的每个邻接点W->AdjV
    for (W = Graph->G[V].FirstEdge; W; W = W->Next)
        if (!Visited[W->AdjV])              //若W->AdjV未被访问
            DFS(Graph, W->AdjV, Visit);     //递归访问
}