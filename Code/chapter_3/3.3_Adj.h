//图的邻接表头文件
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MaxVertexNum 100            //最大顶点数为100
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

//邻接点的定义
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode {
    Vertex AdjV;                    //邻接点下标
    WeightType Weight;              //边权重
    PtrToAdjVNode Next;             //指向下一个邻接点的指针
};

//顶点表头节点的定义
typedef struct VNode {
    PtrToAdjVNode FirstEdge;        //边表头指针
    DataType Data;                  //存顶点的数据
    //注意：很多情况下，顶点无数据，此时Data可以不用出现
} AdjList[MaxVertexNum];            //AdjList是邻接表类型

//图结点的定义
typedef struct GNode *PtrToGNode;
struct GNode {
    int Nv;                         //顶点数
    int Ne;                         //边数
    AdjList G;                      //邻接表
};
typedef PtrToGNode LGraph;          //以邻接表方式存储的图类型
