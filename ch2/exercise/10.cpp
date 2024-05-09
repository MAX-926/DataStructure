// a[0:6] = {3, 2, 6, 5, 9, 4, 8} 
#include<iostream>
#include"../../../MyTool.h"
#include"../../ch1/exercise/1-37.cpp"

template<class T>
void mySelectionSort(T a[], int n)
{
    int indexOfMax = 0;
    for(int i = n-1; i > 0; i--)
    {
        for(int j = 0; j <= i; j++)
            if(a[j] > a[indexOfMax])
                indexOfMax = j;
        std::swap(a[i], a[indexOfMax]);
        indexOfMax = 0;
    }
}

template<class T>
void selectionSort(int a[], int n)
{
    for(int i = n-1; i >= 0; i--)
    {
            T target = indexOfMax(a, i+1);
            std::swap(a[i], a[target]);
    }
}

int main()
{
    int a[7] = {3, 2, 6, 5, 9, 4, 8};
    selectionSort<int>(a, GETSIZE(a));
    print_1D_array_incpp<int>(a, GETSIZE(a));
}

//3, 2, 6, 5, 9, 4, 8
//3, 2, 6, 5, 8, 4, 9
//3, 2, 6, 5, 4, 8, 9
//3, 2, 4, 5, 6, 8, 9
//3, 2, 4, 5, 6, 8, 9
//2, 3, 4, 5, 6, 8, 9