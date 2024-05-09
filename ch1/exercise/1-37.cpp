#include<iostream>
#include"../../Tool.h"
using namespace std;

template<class T>
int indexOfMax(T a[], int n)
{//查找数组a[0:n-1]的最大元素
    if(n <= 0) throw illegalParameter("n must > 0");
    int indexOfMap = 0;
    for(int i = 1; i < n; i++)
        if(a[i] > a[indexOfMap])
            indexOfMap = i;
    return indexOfMap;
}

// int main()
// {
//     int a[] = {1};
//     indexOfMax(a, 0);
// }  