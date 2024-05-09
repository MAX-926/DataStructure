// #include<iostream>
// using namespace std;
#include<stdio.h>
template<class T>
void swap(T& x, T& y)
{
    T temp = x;
    x = y;
    y = temp;
    return;
}

int main()
{
    int a = 3;
    int b = 4;
    swap<int>(a, b);
    printf("%d %d", a, b);
}