//在图（邻接矩阵）中找两点间的最短路径
//哈利波特要念咒语变动物，不同动物要念的咒语长度不同（权重）
//动物可以看作顶点，咒语长度作为边，构建无向图矩阵
#include <stdio.h>
#include "3.8.h"

void FindAnimal(MGraph Graph);
WeightType FindMaxDist(WeightType D[][MaxVertexNum], Vertex i, int N);
void Floyd(MGraph Graph, WeightType D[][MaxVertexNum]);

//程序框架
int main()
{
    //读入图
    MGraph G = BuildGraph();
    //分析图
    FindAnimal(G);

    return 0;
}

//选择动物
void FindAnimal(MGraph Graph)
{
    WeightType D[MaxVertexNum][MaxVertexNum], MaxDist, MinDist;
    Vertex Animal, i;

    Floyd(Graph, D);

    MinDist = INFINITY;
    for (i = 0; i < Graph->Nv; i++)
    {
        MaxDist = FindMaxDist(D, i, Graph->Nv);
        //说明有从i无法变出的动物
        if (MaxDist == INFINITY)
        {
            printf("0\n");
            return;
        }
        //找到最长距离更小的动物
        if (MinDist > MaxDist)
        {
            MinDist = MaxDist;
            Animal = i + 1;         //更新距离，记录编号
        }
    }
    printf("%d %d\n", Animal, MinDist);
}

//找最长距离
WeightType FindMaxDist(WeightType D[][MaxVertexNum], Vertex i, int N)
{
    WeightType MaxDist;
    Vertex j;

    MaxDist = 0;
    //找出i到其他动物j的最长距离
    for (j = 0; j < N; j++)
        if (i != j && D[i][j] > MaxDist)
            MaxDist = D[i][j];

    return MaxDist;
}

//改变过的Floyd算法
void Floyd(MGraph Graph, WeightType D[][MaxVertexNum])
{
    Vertex i, j, k;

    //初始化
    for (i = 0; i < Graph->Nv; i++)
    {
        for (j = 0; j < Graph->Nv; j++)
        {
            D[i][j] = Graph->G[i][j];
        }
    }
    for (k = 0; k < Graph->Nv; k++)
    {
        for (i = 0; i < Graph->Nv; i++)
        {
            for (j = 0; j < Graph->Nv; j++)
            {
                if(D[i][k] + D[k][j] < D[i][j])
                {
                    D[i][j] = D[i][k] + D[k][j];
                }
            }
        }
    }
}