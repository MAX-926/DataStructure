#include"../../../MyTool.h"
#include<iostream>
using namespace std;

//1-31 rSum()
template<class T>
T rSum(T a[], int n)
{
    if(n == 1) return a[0];
    else return a[n-1] + rSum(a, n-1);
}

//計算1-31的程序步
template<class T>
T rSumSC(T a[], int n, int* scp)
{
    if(n < 0) throw IllegalParameter("n must > 0");
    if(n == 1)//if是一個程序步
    { 
        (*scp)++;
        (*scp)++;
        return a[0];//return是一個程序步
    }
    else
    {
        (*scp)++;
        return a[n-1] + rSumSC(a, n-1, scp);//return是一個程序步
    }
}

int main()
{
    int a[] = {-1, -2, -3};
    int sc = 0;
    try
    {
    cout << rSumSC<int>(a, GETSIZE(a), &sc) << endl;
    }catch(IllegalParameter ip)
    {
        ip.outputMessage();
    }
    cout << sc;
}