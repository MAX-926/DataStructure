//函数minmax查找数组a的最大元素和最小元素，令n为实例特征，试问a的元素之间有多少次比较？

#include"../../../MyTool.h"

//比较次数2(n-1)
template<class T>
void minmax(T a[], int n, int &indexOMax, int &indexOfMin)
{
    int cmpc = 0;
    indexOfMin = indexOMax = 0;
    for(int i = 1; i < n; i++)
    {
        if((a[i] > a[indexOMax])* ++cmpc ){ indexOMax = i;}
        if((a[i] < a[indexOfMin])* ++cmpc ){ indexOfMin = i;}
    }
    std::cout << "max: " << indexOMax << std::endl << "min: " << indexOfMin << std::endl;
    std::cout << "cmpc: " << cmpc << std::endl;
}

//最好比较次数：n-1,最坏比较次数：2(n-1)
template<class T>
void minmax(T a[], int n)
{
    T min, max;
    int cmpc = 0;
    min = max = a[0];
    for(int i = 1; i < n; i++)
        if((a[i] > max)*++cmpc) max = a[i];
        else if((a[i] < min)*++cmpc) min = a[i];
    std::cout << "max: " << max << std::endl << "min: " << min << std::endl;
    std::cout << "cmpc: " << cmpc << std::endl;
}

int main()
{
    int a[] = {1, 1, 1, 1, 1};
    int max, min;
    minmax<int>(a, GETSIZE(a), max, min);
    minmax<int>(a, GETSIZE(a));
} 