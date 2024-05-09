//1-30
#include<iostream>
#include"../../../MyTool.h"

template<class T>
T sumB(T a[], int n)
{
    T theSum = 0;
    for(int i = 0; i < n; i++)
        theSum += a[i];
    return theSum;
}

//计算1-30的程序步数
template<class T>
T sum(T a[], int n)
{
    int stepCount = 0;//程序步
    T theSum = 0;
    stepCount++;
    for(int i = 0; i < n; i++)
    {

        stepCount++;
        theSum += a[i];//程序步
        stepCount++;
    }
    stepCount++;
    stepCount++;
    std::cout << "stepCount: " << stepCount << std::endl;
    return theSum;//程序步
}



int main()
{
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::cout << sum<int>(a, GETSIZE(a));
}