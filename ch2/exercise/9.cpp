#include"../../../MyTool.h"
#include<iostream>
#include<string>
#include<cstring>

template<class T>
void rank(T a[], int n, int r[])
{
    memset(r, 0, sizeof(int)*n);
    for(int i = 1; i < n; i++)
        for(int j = 0; j < i; j++)
            if(a[j] <= a[i]) r[i]++;
            else r[j]++;
    return;
}

int main()
{
    int a[] = {3, 2, 6, 5, 9, 4, 7, 1, 8};
    int r[GETSIZE(a)];
    rank(a, GETSIZE(a), r);
    print_1D_array_incpp<int>(a, GETSIZE(a));
    std::cout << std::endl;
    print_1D_array_incpp<int>(r, GETSIZE(r));
}