#include<iostream>
#include"../../Tool.h"
using namespace std;

template<class T>
void iota(T value, T* ta, int size)
{
    for(int i = 0; i < size; i++)
    {
        ta[i] = value + i;
    }
    return;
}

int main()
{
    int a[] = {1, 2, 3, 4, 5, 6};
    int len = sizeof(a)/sizeof(*a);
    iota<int>(26, a, len);
    output_1dArray(a, len);
}
