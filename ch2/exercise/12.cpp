// bubleSort
//a[] = {3, 2, 6, 5, 9, 4, 8}
#include<iostream>
#include"11.cpp"
#include"../../../MyTool.h"

template<class T>
void bubleSort(T a[], int n)
{
    for(int i = n; i > 1; i--)
        buble<int>(a, i);
}

int main()
{
    int a[] = {3, 2, 6, 5, 9, 4, 8};
    bubleSort<int>(a, GETSIZE(a));
    print_1D_array_incpp<int>(a, GETSIZE(a));
}