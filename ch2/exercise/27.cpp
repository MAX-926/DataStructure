#include"../../../MyTool.h"

// template<class T>
// int rSequentialSearch(T a[], int n, const T &x)
// {
//     if(n < 1) return -1;
//     else
//     {
//         if(a[n-1] == x) return n-1;
//         else return rSequentialSearch(a, n-1, x);
//     }
// }

//最好情况：比较次数为1， 最坏情况：比较次数为n
template<class T>
int rSequentialSearch(T a[], int n, const T &x)
{
    if(n < 1) return -1;
    // else
    // {
    if(a[n-1] == x) return n-1;
    return rSequentialSearch(a, n-1, x);
    // }
}


int main()
{
    int a[] = {1, 2, 3, 4, 5};
    std::cout << rSequentialSearch<int>(a, GETSIZE(a), 3);
}