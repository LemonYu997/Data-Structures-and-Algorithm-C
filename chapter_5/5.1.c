//散列函数

//陈留余数法    数字
int Hash1(int Key, int TableSize)
{
    return Key % TableSize;
}

//移位法        字符
int Hash2(const char *Key, int TableSize)
{
    unsigned int h = 0;     //散列函数值，初始化为0
    while (*Key != '\0')    //位移映射
        h = (h << 5) + *Key++;
    return h % TableSize;
}