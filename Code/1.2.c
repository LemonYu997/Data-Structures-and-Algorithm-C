#include <stdio.h>
#include <windows.h>

void PrintN(int N);

int main()
{
    PrintN(1000);

    system("pause");
    return 0;
}

void PrintN(int N)
{
    if (N)
    {
        PrintN(N - 1);
        printf("%d\n", N);
    }
}