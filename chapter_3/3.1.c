//图的 邻接矩阵 表示法
#include <stdio.h>
#include <stdlib.h>

#define MaxVertexNum 100            //最大顶点数为100
#define INFINITY 65535              //∞值设为65535
typedef int Vertex;                 //用顶点下标表示顶点，为整型
typedef int WeightType;             //边的权重设为整形
typedef char DataType;              //顶点存储的数据类型设为字符型

//边的定义
typedef struct ENode *PtrToENode;
struct ENode {
    Vertex V1, V2;                  //有向边<v1, v2>
    WeightType Weight;              //权重
};
typedef PtrToENode Edge;

//图结点的定义
typedef struct GNode *PtrToGNode;
struct GNode {
    int Nv;                         //顶点数
    int Ne;                         //边数
    //构建邻接矩阵
    WeightType G[MaxVertexNum][MaxVertexNum];
    DataType Data[MaxVertexNum];    //存顶点的数据
    //注意：很多情况下，顶点无数据，此时Data[]可以不用出现
} ;
typedef PtrToGNode MGraph;          //以邻接矩阵存储的图类型

//初始化一个有VertexNum个顶点但是没有边的图
MGraph CreateGtaph(int VertexNum)
{
    Vertex V, W;
    MGraph Graph;

    //建立图
    Graph = (MGraph)malloc(sizeof(struct GNode));
    Graph->Nv = VertexNum;
    Graph->Ne = 0;
    //初始化邻接矩阵
    //注意：默认顶点编号从0开始，到(Graph->Nv - 1)
    for (V = 0; V < Graph->Nv; V++)
        for (W = 0; W < Graph->Nv; W++)
            Graph->G[V][W] = INFINITY;

    return Graph;
}

//插入 边<V1, V2>
void InsertEdge(MGraph Graph, Edge E)
{
    Graph->G[E->V1][E->V2] = E->Weight;
    //若是无向图，还要插入边<V1, V2>
    Graph->G[E->V2][E->V1] = E->Weight;
}

//根据输入建立邻接矩阵 图
MGraph BuildGraph()
{
    MGraph Graph;
    Edge E;
    Vertex V;
    int Nv, i;

    scanf("%d", &Nv);               //读入顶点个数
    //初始化有Nv个顶点但没有边的图
    Graph = CreateGtaph(Nv);

    scanf("%d", &(Graph->Ne));      //读入边数
    //如果有边
    if (Graph->Ne != 0)
    {   
        //建立边结点
        E = (Edge)malloc(sizeof(struct ENode));
        //读入边，格式为"起点 终点 权重"，插入邻接矩阵
        for (i = 0; i < Graph->Ne; i++)
        {
            scanf("%d %d %d", &E->V1, &E->V2, &E->Weight);
            //注意：如果权重不是整形，Weight的读入格式要改
            InsertEdge(Graph, E);
        }
    }

    //如果顶点有数据的话，读入数据
    for (V = 0; V < Graph->Nv; V++)
        scanf(" %c", &(Graph->Data[V]));

    return Graph;
}
