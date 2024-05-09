#include<iostream>
#include"../../../MyTool.h"

//2n+2
template<class T>
T t1(int n)
{
    if(n == 0) return 2;
    else return 2 + t1<int>(n-1);
}

template<class T>
T t2(int n)
{
    if(n == 0) return 0;
    if(n == 1) return 1;
    else if(n > 1) return 1 + t2<int>(n-2);
    else throw IllegalParameter("n must > 0");
}

int main()
{
    std::cout << t2<int>(8);
}