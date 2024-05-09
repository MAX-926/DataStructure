//低效的前缀求和
#include"../../../MyTool.h"

template<class T>
T sum(T a[], int n)
{
    T theSum = 0;
    for(int i = 0; i < n; i++)
        theSum += a[i];
    return theSum;
}

//前缀求和
template<class T>
void inef(T a[], T b[], int n)
{
    for(int j = 0; j < n; j++)
        b[j] = sum<int>(a, j+1);
}

int main()
{
    int a[] = {1, 2, 3, 4, 5};
    int len = GETSIZE(a);
    int b[len];
    inef<int>(a, b, len);
    print_1D_array_incpp<int>(b, len);
}