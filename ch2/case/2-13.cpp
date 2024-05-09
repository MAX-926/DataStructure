#include"E:\thinking in C++\MyTool.h"
#include<iostream>
using namespace std;

template<class T>
void buble(T a[], int n, bool *sorted)
{
    *sorted = true;
    for(int i = 0; i < n; i++)
        if(a[i] <a[i-1])
        { 
            swap(a[i], a[i-1]);
            *sorted = false;
        }
}

template<class T>
void bubleSort_in_time(T a[], int n)
{
    int i;
    bool sorted = false;
    for(i = n-1 ; !sorted && (i > 0); i--)
        buble<T>(a, i+1, &sorted);
    cout << "i: " << i << endl;
}

//范本
template<class T>
bool bubleTxt(T a[], int n)
{
    bool swapped = false;
    for(int i = 0; i < n-1; i++)
    {
        if(a[i] > a[i+1])
        { 
            swap(a[i], a[i+1]);
            swapped = true;
        }
    }
    return swapped;
}

template<class T>
void bubleSort(int a[], int n)
{
    int i;
    for(i = n; (i > 0) && bubleTxt(a, i); i--);
    // for(i = n; (i > 1) && bubleTxt(a, i); i--);
    cout << "i: " << i << endl;
}


int main()
{
    int a[] = {3, 2, 1};
    // int len = GETSIZE(a);
    bubleSort<int>(a, GETSIZE(a));
    print_1D_array_incpp<int>(a, GETSIZE(a));   
}