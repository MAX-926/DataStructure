//创建一个数组a，使函数rearrange（见程序2-11）执行n-1次元素交换和n-1次名次交换。

#include"../../../MyTool.h"

template<class T>
void rank(T a[], int n, int r[])
{
    for(int i = 1; i < n; i++)
        for(int j = 0; j < i; j++)
            if(a[i] >= a[j]) r[i]++;
            else r[j]++;
}

template<class T>
void rearrange(T a[], int n, int r[])
{
    int count = 0;
    for(int i = 0; i < n; i++)
        while(i != r[i])
        {
           std::swap(a[i], a[r[i]]);
           std::swap(r[i], r[r[i]]);
           count++;
        }
    std::cout << "n-1: " << n-1 << std::endl;
    std::cout <<"count: " << count << std::endl;
}

int main()
{
    // int a[] = {5, 3, 4, 1, 2};
    // pair递增组合(第一个元素最大， 元素对呈现递增安排, 最后一对是递增即可)
    // int a[] = {6, 3, 4, 5, 1, 2};
    // int a[] = {7, 5, 6, 3, 4, 1, 2}
    int a[] = {8, 3, 4, 5, 6, 7, 1, 2};
    int r[GETSIZE(a)] = {0};
    rank(a, GETSIZE(r), r);
    rearrange<int>(a, GETSIZE(a), r);
    // print_1D_array_incpp<int>(a, GETSIZE(a));
}