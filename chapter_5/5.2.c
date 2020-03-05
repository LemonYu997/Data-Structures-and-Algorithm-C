//散列表——冲突处理方法——平方探测法——数字类型
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define MAXTABLESIZE 100000         //允许开辟的最大散列表长度
typedef int ElementType;            //关键词类型用整型
typedef int Index;                  //散列地址类型
typedef Index Position;             //数据所在位置与散列地址是同一类型
//散列单元状态类型，分别对应：有合法元素、空单元、有已删除元素
typedef enum
{
    Legitimate,                     //枚举，默认值为0，合法元素
    Empty,                          //为1，空单元
    Delete                          //为2，有已删除元素
} EntryType;

typedef struct HashEntry Cell;      //散列表单元类型
struct HashEntry {
    ElementType Data;               //存放元素
    EntryType Info;                 //单元状态
};

typedef struct TblNode *HashTable;  //散列表类型
struct TblNode {                    //散列表节点定义
    int TableSize;                  //表的最大长度
    Cell *Cells;                    //存放散列单元数据的数组
};

//一个简单的散列函数
Index Hash(ElementType Key, int TableSize)
{
    return Key % TableSize;
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
    //保证散列表的最大长度是素数
    H->TableSize = NextPrime(TableSize);
    //声明单元数组
    H->Cells = (Cell *)malloc(H->TableSize * sizeof(Cell));
    //初始化单元状态为 空单元
    for (i = 0; i < H->TableSize; i++)
        H->Cells[i].Info = Empty;

    return H;
}

//查找函数
Position Find(HashTable H, EntryType Key)
{
    Position CurrentPos, NewPos;
    int CNum = 0;                   //记录冲突次数

    //初始散列位置
    //用一个简单的Hash函数完成操作
    NewPos = CurrentPos = Hash(Key, H->TableSize);

    //当该位置的单元非空，并且不是要找的元素时，发生冲突
    //如果是字符串类型的关键字需要strcmp函数
    while (H->Cells[NewPos].Info != Empty && H->Cells[NewPos].Data != Key)
    {
        //统计1此冲突，并判断奇偶次
        if (++CNum % 2 )            //奇数次冲突
        {   
            //增量为 +[(CNum + 1) / 2] ^ 2
            NewPos = CurrentPos + (CNum + 1) * (CNum + 1) / 4;
            //如果超出了地址界限，调整为合法地址
            while (NewPos >= H->TableSize)
                NewPos = NewPos % H->TableSize;
        }
        else                        //偶数次冲突
        {
            //增量为-(CNum / 2) ^ 2
            NewPos = CurrentPos - CNum * CNum / 4;
            //调整为合法地址
            while (NewPos < 0)
                NewPos += H->TableSize;
        }
    }
    //此时NewPos或者是Key的位置，或者是一个空单元的位置（表示找不到）
    return NewPos;
}

//插入函数
bool Insert(HashTable H, ElementType Key)
{
    //先检查Key是否已存在
    Position Pos = Find(H, Key);

    //如果这个单元没有被占，说明Key可以插入在此
    if (H->Cells[Pos].Info != Legitimate)
    {
        H->Cells[Pos].Info = Legitimate;
        H->Cells[Pos].Data = Key;
        //字符串类型的关键字需要strcpy()函数
        return true;
    }
    else
    {
        printf("Key already exists.\n");
        return false;
    }
}
