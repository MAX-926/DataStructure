#include"..    /../../MyTool.h"
//最坏情况下，x与a的元素有n+1次比较
//与2-1相比，在最坏情况下2-26的运行更快，因为同样执行n+1次循环，2-1还需要做i与n的比较，相对来说运行更慢。
//最好情况同理
template<class T>
int sequentialSearch(T a[], int n, const T &x)
{
    a[n] = x;
    int i;
    for(i = 0; a[i] != x; i++);
    if(i == n) return -1;
    return i;
}

int main()
{
    int a[] = {1, 2, 3, 4, 5, 0};
    std::cout << sequentialSearch<int>(a, GETSIZE(a)-1, 6);
}