//及时终止冒泡排序
//a[] = {4, 2, 6, 7, 1, 0, 9, 8, 5, 3}

#include"../../../MyTool.h"


template<class T>
void buble(T a[], int n, bool *stag)
{
    *stag = true;
    for(int i = 0; i < n-1; i++)
        if(a[i] > a[i+1])
        {
             std::swap(a[i], a[i+1]);
             *stag = false;
        }
}

template<class T>
void BubleSort_in_time(T a[], int n)
{
    bool sorted = false;
    int i;
    for(i = n-1; i > 0 && !sorted; i--)
        buble<T>(a, i+1, &sorted);
    std::cout << i << std::endl;
}

int main()
{
    int a[] = {4, 2, 6, 7, 1, 0, 9, 8, 5, 3};
    BubleSort_in_time<int>(a, GETSIZE(a));
    print_1D_array_incpp<int>(a, GETSIZE(a));
}

//4, 2, 6, 7, 1, 0, 9, 8, 5, 3
//2, 4, 6, 1, 0, 7, 8, 5, 3, 9
//2, 4, 1, 0, 6, 7, 5, 3, 8, 9
//2, 1, 0, 4, 6, 5, 3, 7, 8, 9
//1, 0, 2, 4, 5, 3, 6, 7, 8, 9
//0, 1, 2, 4, 3, 5, 6, 7, 8, 9
//0, 1, 2, 3, 4, 5, 6, 7, 8, 9 