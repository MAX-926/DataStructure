//a[0:6] = {3, 2, 6, 5, 9, 4, 8}
//实施程序2-8的冒泡过程
#include<iostream>
#include"../../../MyTool.h"

template<class T>
void buble(T a[], int n)
{
    for(int i = 1; i < n; i++)
        if(a[i] < a[i-1]) std::swap(a[i], a[i-1]);
}

// int main()
// {
//     int a[] = {3, 2, 6, 5, 9, 4, 8};// 2, 3, 5, 6, 4, 8, 9
//     buble<int>(a, GETSIZE(a));
//     print_1D_array_incpp<int>(a, GETSIZE(a));
// }