#include<iostream>
using namespace std;

template<class T>
int myCount(int value, T* ta, int size)
{
    int re = 0;
    for(int i = 0; i < size; i++)
        if(ta[i] == value) re++;
    return re;
}

template<class T>
int count(T a[], int n, T value)
{
    int c = 1;
    for(int i  = 0; (i < n-1) && (a[i] == value? c++: 1); i++);
    return c-1;
}

int main()
{
    int a[] = {1, 1, 1, 4, 7, 4, 5, 0, 8, 9, 4, 2};
    int len = sizeof(a)/sizeof(*a);
    cout << count<int>(a, len, 4);
}