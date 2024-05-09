//a[] = {4, 2, 6, 7, 1, 0, 9, 8, 5, 3}
#include"../../../MyTool.h"

template<class T>
void insert(T a[], int n, const T &x)
{
    int i;
    for(i = n-1; i >= 0; i--)
        if(a[i] > x)
            a[i+1] = a[i];
        else
        {
            a[i+1] = x;
            break;
        }
    if(i == -1) a[i+1] = x;
}

template<class T>
void insertionSort(T a[], int n)
{
    for(int i = 1; i < n; i++)
    {
        T tmp = a[i];
        insert<int>(a, i, tmp);
    }
}

int main()
{
    int a[] = {4, 2, 6, 7, 1, 0, 9, 8, 5, 3};
    insertionSort(a, GETSIZE(a));
    print_1D_array_incpp<int>(a, GETSIZE(a));
}

//4, 2, 6, 7, 1, 0, 9, 8, 5, 3
//2, 4, 6, 7, 1, 0, 9, 8, 5, 3
//2, 4, 6, 7, 1, 0, 9, 8, 5, 3
//1, 2, 4, 6, 7, 0, 9, 8, 5, 3
//0, 1, 2, 4, 6, 7, 9, 8, 5, 3
//0, 1, 2, 4, 6, 7, 9, 8, 5, 3
//0, 1, 2, 4, 6, 7, 8, 9, 5, 3
//0, 1, 2, 4, 5, 6, 7, 8, 9, 3
//0, 1, 2, 3, 4, 5, 6, 7, 8, 9