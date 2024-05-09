#include<iostream>
using namespace std;

template<class T>
void bubleSort(T a[], int n)// (n*(n-1))/2次比较
{
    for(int i = n-1; i > 0; i--)// n-1
        for(int j = 1; j <= i; j++)// n-1、n-2...、1
            if(a[j] < a[j-1])
                swap(a[j], a[j-1]);
}
// 分离式定义
template<class T>
void buble(T a[], int n)
{
    for(int i = 1; i < n; i++)
        if(a[i] < a[i-1]) 
            swap(a[i], a[i-1]);
}

template<class T>
void bubleSortDisDef(T a[], int n)
{
    for(int i = n; i > 1; i--)
        buble(a, i);
}


int main()
{
    int a[] = {6, 4, 32,6, 7, 3, 742, 6235, 42, 536, 86, 34};
    int len = sizeof(a)/sizeof(a[0]);
    bubleSortDisDef<int>(a, len);
    for(int i = 0; i < len; i++)
        cout << a[i] << " ";
}