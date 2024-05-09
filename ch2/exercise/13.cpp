#include"../../../MyTool.h"
#include<iostream>

template<class T>
void insert(T a[], int n, const T &x)
{
    int i;
    for(i = n-1; i >= 0 && a[i] > x; i--)
        a[i+1] = a[i];
    a[i+1] = x;    
}

int main()
{
    int a[] = {1, 2, 4, 6, 7, 8, 9, 0};
    insert<int>(a, GETSIZE(a)-1, 3);
    print_1D_array_incpp<int>(a, GETSIZE(a));
}