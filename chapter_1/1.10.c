//多项式加法和乘法的链表实现
#include <stdio.h>
#include <stdlib.h>

typedef struct PolyNode *Polynomial;
struct PolyNode {
    int coef;                   //系数
    int expon;                  //指数
    Polynomial link;            //下一项
};

Polynomial ReadPoly();
void Attach(int c, int e, Polynomial *pRear);
Polynomial Add(Polynomial P1, Polynomial P2);
int Compare(int a, int b);
Polynomial Mult(Polynomial P1, Polynomial P2);
void PrintPoly(Polynomial P);

int main()
{
    Polynomial P1, P2, PP, PS;

    P1 = ReadPoly();                //读入P1
    P2 = ReadPoly();                //读入P2
    PP = Mult(P1, P2);              //PP存放P1和P2的积
    PrintPoly(PP);                  //输出PP
    PS = Add(P1, P2);               //PS存放P1和P2的和
    PrintPoly(PS);                  //输出PS

    return 0;
}

//读入多项式
//使Rear指向一个空节点
Polynomial ReadPoly()
{
    Polynomial P, Rear, t;
    int c, e, N;

    scanf("%d", &N);                    //多项式项数
    P = (Polynomial)malloc(sizeof(struct PolyNode));        //创建一个链表头空节点
    P->link = NULL;                     //刚开始只有一个空节点
    Rear = P;                           //Rear指向第一个节点
    while(N--)
    {
        scanf("%d %d", &c, &e);         //读入系数和指数
        Attach(c, e, &Rear);            //创建一个新节点并将其接在上一个节点后边，对第一次调用来说就是接在Rear空节点后边
    }
    
    t = P;
    P = P->link;                        //使P从空节点的下一个节点即有数据的节点开始
    free(t);                            //释放空节点

    return P;
}

//创建一个新节点赋值并接在上一个节点后边
void Attach(int c, int e, Polynomial *pRear)
{
    Polynomial P;

    P = (Polynomial)malloc(sizeof(struct PolyNode));        //申请一个新节点
    //对新节点赋值
    P->coef = c;
    P->expon = e;
    P->link = NULL;
    //将P指向的新节点插入到当前结果表达式尾项的后面
    (*pRear)->link = P;                                     //*pRear是Rear的指针，所以该行表示尾项Rear的下一项指向新节点P
    *pRear = P;                                             //然后把尾项移到P上
}

//多项式相加
Polynomial Add(Polynomial P1, Polynomial P2)
{
    Polynomial t1, t2, P, Rear, temp;                 //P是结果多项式队头，Rear是队尾
    t1 = P1;
    t2 = P2;
    int sum;

    P = (Polynomial)malloc(sizeof(struct PolyNode));        //申请一个新节点，用来存放结果
    P->link = NULL;
    Rear = P;
    while(t1 && t2)                 //当两个多项式都有非零项待处理时
    {
        switch(Compare(t1->expon, t2->expon))               //比较两个指数
        {
            case 1:                                         //t1中的指数较大
                Attach(t1->coef, t1->expon, &Rear);            //将t1中此时节点接在结果链表上
                t1 = t1->link;                              //t1向后挪一位
                break;
            case -1:                                        //t2中的指数较大
                Attach(t2->coef, t2->expon, &Rear);
                t2 = t2->link;
                break;
            case 0:
                sum = t1->coef + t2->coef;
                if (sum)                                    //当系数和不为0时才创建新节点
                    Attach(sum, t1->expon, &Rear);
                t1 = t1->link;
                t2 = t2->link;
                break;
        }
    }
    //将未处理完的另一个多项式的所有节点依次复制到结果多项式中
    while(t1)
    {
        Attach(t1->coef, t1->expon, &Rear);
        t1 = t1->link;
    }
    while(t2)
    {
        Attach(t2->coef, t2->expon, &Rear);
        t2 = t2->link;
    }

    Rear->link = NULL;
    temp = P;
    P = P->link;
    free(temp);             //释放临时空表头

    return P;
}

int Compare(int a, int b)
{
    if (a > b)
        return 1;
    else if (a < b)
        return -1;
    else
        return 0;
}

//两个多项式相乘
Polynomial Mult(Polynomial P1, Polynomial P2)
{
    Polynomial P, Rear, t1, t2, t;
    int c, e;

    if (!P1 || !P2)
        return NULL;

    t1 = P1;
    t2 = P2;
    P = (Polynomial)malloc(sizeof(struct PolyNode));        //创建新节点
    P->link = NULL;
    Rear = P;
    
    while(t2)       //先计算P1的第一项乘以P2的每一项得到P
    {
        Attach(t1->coef * t2->coef, t1->expon + t2->expon, &Rear);      //系数相乘，指数相加
        t2 = t2->link;
    }
    t1 = t1->link;
    //计算t1的每一项乘以t2的每一项
    while (t1)          //遍历t1的每一项
    {
        t2 = P2;
        Rear = P;
        while (t2)      //遍历t2的每一项
        {
            e = t1->expon + t2->expon;                          
            c = t1->coef * t2->coef;
            //判断插入的位置
            while (Rear->link && Rear->link->expon > e)             //以指数排序，如果当前节点之后的指数大于新节点的指数就往后挪                   
                Rear = Rear->link;                  
            if (Rear->link && Rear->link->expon == e)               //如果指数相等就进行合并
            {
                if (Rear->link->coef + c)                           //相加结果不为0是就系数相加
                    Rear->link->coef += c;
                else                                                //相加结果为0时就释放掉该节点
                {
                    t = Rear->link;
                    Rear->link = t->link;
                    free(t);
                }
            }
            else                                                    //如果新节点指数大于当前节点之后的指数，就插入
            {
                t = (Polynomial)malloc(sizeof(struct PolyNode));    //申请新节点
                //新节点赋值
                t->coef = c;
                t->expon = e;
                t->link = Rear->link;
                //将t插入，并把队尾向后挪
                Rear->link = t;
                Rear = Rear->link;
            }
        }
    }

    //释放队头空节点
    t2 = P;
    P = P->link;
    free(t2);

    return P;
}

//输出多项式
void PrintPoly(Polynomial P)
{
    int flag = 0;                   //辅助调整输出格式用

    if (!P)                         //如果为空就输出0 0 
    {
        printf("0 0\n");
        return;
    }

    while (P)
    {
        if (!flag)                  //输出格式为 X X _ X X，第一项前不加空格，后边每一项都加空格
            flag = 1;
        else
            printf(" ");
        printf("%d %d", P->coef, P->expon);
        P = P->link;
    }
    printf("\n");
}