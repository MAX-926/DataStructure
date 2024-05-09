#include<iostream>
#include"../../../MyTool.h"
// using namespace std;

//精简版
template<class T>
T sumE(T a[], int n)
{
    int stepCount = 0;//程序步
    // T theSum = 0;
    for(int i = 0; i < n; i++)
    // {
        stepCount += 2;
        // theSum += a[i];//程序步
    // }
    stepCount += 3;
    std::cout << "stepCount: " << stepCount << std::endl;
    // return theSum;//程序步
    return 0;
}

int main()
{
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::cout << "2*n + 3:" << sumE(a, GETSIZE(a));
}