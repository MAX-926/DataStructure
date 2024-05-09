//在函数sum的for循环中执行了多少次加法
//n次
#include"../../../MyTool.h"

template<class T>
T sum(T a[], int n)
{
    T theSum = 0;
    for(int i = 0; i < n; i++)
        theSum += a[i];
    return theSum;
}

int main()
{
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::cout << sum(a, GETSIZE(a));
}