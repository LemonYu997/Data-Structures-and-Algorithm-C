//实例：电话狂人
//输入一个次数，和每次的电话聊天双方号码，得到一个打电话次数最多的号码
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

#define MAXTABLESIZE 100000                 //允许开辟的最大散列表长度
#define KEYLENGTH 11                        //关键字符串的最大长度
typedef char ElementType[KEYLENGTH + 1];    //关键词类型用字符串
typedef int Index;                          //散列地址类型

/******************单链表的定义*********************/
typedef struct LNode *PtrToLNode;
struct LNode {
    ElementType Data;
    PtrToLNode Next;
    int Count;                              //电话出现的次数
};
typedef PtrToLNode Position;
typedef PtrToLNode List;
/******************单链表的定义*********************/

typedef struct TblNode *HashTable;          //散列表类型
struct TblNode {                            //散列表节点定义
    int TableSize;                          //表的最大长度
    List Heads;                             //指向链表头节点的数组
};

int Hash(int Key, int P);
int NextPrime(int N);
HashTable CreateTable(int TableSize);
Position Find(HashTable H, ElementType Key);
bool Insert(HashTable H, ElementType Key);
void DestroyTable(HashTable H);
void ScanAnOutPut(HashTable H);

//主体
int main()
{
    //一、创建散列表
    int N, i;
    ElementType Key;
    HashTable H;

    scanf("%d", &N);
    H = CreateTable(N * 2);                 //创建一个散列表
    for (i = 0; i < N; i++)
    {
        scanf("%s", Key);
        Insert(H, Key);
        scanf("%s", Key);
        Insert(H, Key);
    }
    ScanAnOutPut(H);
    DestroyTable(H);
    
    return 0;
}

//除留余数法
int Hash(int Key, int P)
{
    return Key % P;
}

//返回大于N且不超过MAXTABLESIZE的最小素数
int NextPrime(int N)
{
    int i;
    //从大于N的下一个奇数开始
    int p = (N % 2) ? N + 2 : N + 1;

    while (p <= MAXTABLESIZE)
    {   
        //sqrt(x)函数为返回x的平方根
        for (i = (int)sqrt(p); i > 2; i--)
            if (!(p % i))           //p不是素数
                break;
            if ( i == 2)            //for正常结束，说明p是素数
                break;
            else
                p += 2;             //否则试探下一个奇数
    }
    return p;
}

//创建散列表
HashTable CreateTable(int TableSize)
{
    HashTable H;
    int i;

    H = (HashTable)malloc(sizeof(struct TblNode));
    //保证散列表最大长度是素数
    H->TableSize = NextPrime(TableSize);

    //以下分配链表头节点
    H->Heads = (List)malloc(H->TableSize * sizeof(struct LNode));
    //初始化表头结点
    for (i = 0; i < H->TableSize; i++)
    {
        H->Heads[i].Data[0] = '\0';
        H->Heads[i].Next = NULL;
        H->Heads[i].Count = 0;
    }

    return H;
}

//查找关键词
Position Find(HashTable H, ElementType Key)
{
    Position P;
    Index Pos;

    //初始散列位置
    Pos = Hash(atoi(Key + KEYLENGTH), H->TableSize);
    P = H->Heads[Pos].Next;         //从该链表的第一个节点开始
    //当未到表尾，并且Key未找到时
    while (P && strcmp(P->Data, Key))
        P = P->Next;

    //此时P为指向找到的节点，或者为NULL
    return P;       
}

//插入
bool Insert(HashTable H, ElementType Key)
{
    Position P, NewCell;
    Index Pos;

    P = Find(H, Key);
    //关键词没找到，可以插入
    if (!P)
    {
        NewCell = (Position)malloc(sizeof(struct LNode));
        strcpy(NewCell->Data, Key);
        NewCell->Count = 1;
        Pos = Hash(atoi(Key + KEYLENGTH), H->TableSize);      //初始散列位置
        //将NewCell插入为H->Heads[Pos]链表的第一个节点
        NewCell->Next = H->Heads[Pos].Next;
        H->Heads[Pos].Next = NewCell;
        return true;
    }
    //关键词已存在
    else
    {
        P->Count++;
        return false;
    }
}

//删除表
void DestroyTable(HashTable H)
{
    int i;
    Position P, Tmp;

    //释放每个链表的节点
    for (i = 0; i < H->TableSize; i++)
    {
        P = H->Heads[i].Next;
        while (P)
        {
            Tmp = P->Next;
            free(P);
            P = Tmp;
        }
    }
    free(H->Heads);             //释放头节点数组
    free(H);                    //释放散列表节点
}

//输出狂人
void ScanAnOutPut(HashTable H)
{
    int i, MaxCnt = 0;
    int PCnt = 0;
    ElementType MinPhone;
    List Ptr;
    MinPhone[0] = '\0';
    //扫描链表
    for (i = 0; i < H->TableSize; i++)
    {
        Ptr = H->Heads[i].Next;
        while (Ptr)
        {   
            //更新最大通话次数
            if (Ptr->Count > MaxCnt)
            {
                MaxCnt = Ptr->Count;
                strcpy(MinPhone, Ptr->Data);
                PCnt = 1;
            }
            else if (Ptr->Count == MaxCnt)
            {
                PCnt++;         //狂人计数
                //更新狂人的最小手机号码
                if (strcmp(MinPhone, Ptr->Data) > 0)
                    strcpy(MinPhone, Ptr->Data);        
            }
            Ptr = Ptr->Next;
        }
    }
    printf("%s %d", MinPhone, MaxCnt);
    if (PCnt > 1)
        printf(" %d", PCnt);
    printf("\n");
}