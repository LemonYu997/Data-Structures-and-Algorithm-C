// File Transfer 问题
/* 
判断几台电脑之间是否链接成功
主要函数：
    输入'I m n': m 和 n 两个机器之间建立连接          即集合合并
    输入'C m n': m 和 n 两个机器之间检查链接          即检查是否为同一个集合
    输入'S': 检查整个网络链接是否成功      
方法：
    使用集合
*/

#include <stdio.h>

//集合
#define MaxSize 1000
typedef int ElementType;         
typedef int SetName;                                //用根节点下标做集合名
typedef ElementType SetType[MaxSize];

SetName Find(SetType S, ElementType X);
void Union(SetType S, SetName Root1, SetName Root2);

void Initialization(SetType S, int n);
void Input_connection(SetType S);
void Check_connection(SetType S);
void Check_network(SetType S, int n);

//程序框架
int main()
{
    SetType S;
    int n;              //机器的个数（元素数）
    char in;            //输入的字符
    scanf("%d", &n);
    //初始化集合
    Initialization(S, n);
    do
    {
        scanf("%c", &in);
        switch (in)
        {   
            //建立连接
            case 'I':
                Input_connection(S);
                break;
            //检查链接
            case 'C':
                Check_connection(S);
                break;
            //检查整个网络链接是否成功
            case 'S':
                Check_network(S, n);
                break;
        }
    } while (in != 'S');
    
    return 0;
}

//集合初始化
void Initialization(SetType S, int n)
{   
    //每个元素都设为-1
    int i;
    for (i = 0; i < n; i++)
        S[i] = -1;
}

//输入'I m n': m 和 n 两个机器之间建立连接
void Input_connection(SetType S)
{
    ElementType m, n;
    SetName Root1, Root2;
    scanf("%d %d", &m, &n);
    //机器是从 1 到 n 编号的，而机器对应的下标是从 0 开始的，所以要 -1
    Root1 = Find(S, m - 1);
    Root2 = Find(S, n - 1);
    //如果 m 和 n 不在同一个集合中，即根的下标不同，合并
    if (Root1 != Root2)
    {
        Union(S, Root1, Root2);
        printf("%d and %d connected.\n", m, n);
    }
    //否则两个机器已经连接成功
    else
        printf("Already connected.\n");
}

//输入'C m n': m 和 n 两个机器之间检查链接
void Check_connection(SetType S)
{
    ElementType m, n;
    SetName Root1, Root2;
    scanf("%d %d", &m, &n);
    Root1 = Find(S, m - 1);
    Root2 = Find(S, n - 1);
    //如果两台机器链接成功，即在一个集合
    if (Root1 == Root2)
        printf("yes\n");
    //如果不在同一个集合
    else
        printf("no\n");
}

//输入'S': 检查整个网络链接是否成功
void Check_network(SetType S, int n)
{   
    int i, counter = 0;             //counter是集合数，如为 1，说明所有机器在同一个集合中
    for (i = 0; i < n; i++)
    {   
        //集合的根为-1，查找为-1的数量就知道集合的数量
        if (S[i] < 0)
            counter++;
    }
    //所有机器在同一个集合中
    if (counter == 1)
        printf("The network is connected.\n");
    //有多个集合
    else
        printf("There are %d components.\n", counter);
}

//查找元素 X 是否在集合 S 中
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

/*
输入样例：
5                           //要测试的机器数
C 3 2
no
I 3 2
3 and 2 connected.
C 1 5
no
I 4 5
4 and 5 connected.
I 2 4
2 and 4 connected.
C 3 5
yes
I 1 3
1 and 3 connected.
I 2 5
Already connected.
C 1 5
yes
S
The network is connected.
*/