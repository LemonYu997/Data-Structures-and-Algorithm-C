//图的邻接矩阵头文件
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
