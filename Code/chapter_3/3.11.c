//邻接表存储，拓扑排序算法
#include <stdio.h>
#include <stdbool.h>
#include "3.3_Adj.h"
#include "3.4_queue.h"

//对Graph进行拓扑排序，TopOrder[]顺序存储排序后的顶点下标
bool TopSort(LGraph Graph, Vertex TopOrder[])
{
    int Indegree[MaxVertexNum], cnt;
    Vertex V;
    PtrToAdjVNode W;

    Queue Q = CreateQueue();

    //初始化Indegree[]
    for (V = 0; V < Graph->Nv; V++)
        Indegree[V] = 0;
    
    //遍历图，得到Indegree[]
    for (V = 0; V < Graph->Nv; V++)
        for (W = Graph->G[V].FirstEdge; W; W = W->Next)
            Indegree[W->AdjV]++;        //对有向边<V, W->AdjV>累计终点的入度

    //将所有入度为0的顶点入列
    for (V = 0; V < Graph->Nv; V++)
        if (Indegree[V] == 0)
            AddQ(Q, V);
    
    //下面进入拓扑排序
    cnt = 0;
    while (!IsEmpty(Q))
    {
        //弹出一个入度为0的顶点
        V = DeleteQ(Q);
        //将之存为结果序列的下一个元素
        TopOrder[cnt++] = V;
        //对V的每个邻接点W->AdjV，若删除V使得W->AdjV入度为0，则该顶点入列
        for (W = Graph->G[V].FirstEdge; W; W = W->Next)
            if (--Indegree[W->AdjV == 0])
                AddQ(Q, W->AdjV);
    }

    if (cnt != Graph->Nv)
        return false;       //说明图中有回路，返回不成功标志
    else
        return true;
}