#include<iostream>
using namespace std;

template<class T>
T inner_product(T* ta, T* tb, int size)
{
    T re = 0;
    for(int i = 0; i < size; i++)
        re += ta[i]*tb[i];
    return re;
}

int main()
{
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int b[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int len = sizeof(a)/sizeof(*a);
    cout << inner_product<int>(a, b, len);
    return 0;
}