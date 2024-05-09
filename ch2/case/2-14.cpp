#include<iostream>
#include"../../../MyTool.h"
using namespace std;

template<class T>
void insert(T a[], int n, const T& x)
{
 int i;
    for(i = n-1; i >= 0 && a[i] > x; i--)
        a[i+1] = a[i];
    a[i+1] = x;
    // n++;
}   

template<class T>
void insertionSort(T a[], int n)
{
    for(int i = 1; i < n; i++)
    {
        T t = a[i];
        insert<T>(a, i, t);
    }
    //
}

template<class T>
void myInsert(T a[], int n, const T &x)
{
    int i;
    for(i = n-1; i >= 0 && a[i] > x ; i--)
        a[i+1] = a[i];
    a[i+1] = x;
}

template<class T>
void myInsertionSort(T a[], int n)
{
    for(int i = 1; i < n; i++)
    {
        T t = a[i];
        myInsert<T>(a, i, t);
    }
}

// inline insertionSort
template<class T>
void inlineInsertionSort(T a[], int n)
{
    for(int i = 1; i < n; i++)
    {
        T t = a[i];
        int j;
        for(j = i-1; j >= 0 && a[j] > t; j--)
            a[j+1] = a[j];
        a[j+1] = t;
    }
}

int main()
{
    int a[] = {7, 6, 5, 4, 3, 2, 1};
                                                             inlineInsertionSort<int>(a, GETSIZE(a));
    print_1D_array_incpp<int>(a, GETSIZE(a));
}
