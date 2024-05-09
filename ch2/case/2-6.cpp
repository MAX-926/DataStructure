#include<iostream>
#include"2-5.cpp"
template<class T>
void rearrange(T a[], int n, int r[])
{
    T *tp = new T[n];
    //n
    for(int i = 0; i < n; i++)
    {
        tp[r[i]] = a[i];
    }

    // n
    for(int i = 0; i < n; i++)
        a[i] = tp[i];
    delete []tp;
}

// 这种排序的时间复杂度：n*(n-1)/2 + 2n

// 原地重排的按名次排序
template<class T>
void rearrange_in_place(T a[], int n, int r[])
{
    for(int i = 0; i < n; i++)
    {
        while(i != r[i])
        {
            std::swap(a[i], a[r[i]]);
            std::swap(r[i], r[r[i]]);
        }
    }
}
//与rearrange相比，内存开销变小，但最坏执行时间增加（2*（n-1)）

int main()
{
    int a[] = {4, 3, 9, 3, 7};
    int r[5] = {0};
    // rank<int>(a, 5, r);
    rankN(a, 5, r);
    // for(int i = 0; i < 5; i++)
    //     std::cout << r[i] << " ";
    // std::cout << std::endl;
    rearrange_in_place(a, 5, r);
    for(int i = 0; i < 5; i++)
        std::cout << a[i] << " ";
}