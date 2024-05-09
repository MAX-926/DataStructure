#include"../../../MyTool.h"
template<class T>
int binarySearch(T a[], int left, int right, const T &x)
{
    unsigned int middleIndex = (right + left) >> 1;
    // if((middleIndex == 0 && a[middleIndex] != x) || (middleIndex == right) && x != a[middleIndex]) return -1;
    if(right < left) return -1;
    else if(x == a[middleIndex]) return middleIndex;
    else if(x < a[middleIndex]) binarySearch(a, left, middleIndex-1, x);
    else if(x > a[middleIndex]) binarySearch(a, middleIndex+1, right, x);
}

template<class T>
int BinarySearch(T a[], int n, const T &x)
{
    int left = 0;
    int right = n-1;
    while(left <= right)
    {
        int middleIndex = (left + right) >> 1;
        if(a[middleIndex] == x) return middleIndex;
        else if(a[middleIndex] > x) {right = middleIndex-1; continue;}
        else if(a[middleIndex] < x) left = middleIndex+1;
    }
    return -1;
}

int main()
{
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::cout << binarySearch<int>(a, 0, GETSIZE(a)-1, 10);
    // std::cout << BinarySearch<int>(a, GETSIZE(a), 0);
}