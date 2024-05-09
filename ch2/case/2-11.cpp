#include<iostream>
using namespace std;

template<class T>
int selectionSort(T *a, int n)
{
    int maxIndex = 0;
    int tag = 0;
    int i;
    for(i = n-1; i >= 0; i--)
    {
        for(int j = 1; j <= i; j++)
        {
            if(a[j] >= a[maxIndex])
                maxIndex = j;
            if(a[j] <= a[j+1] && j+1 <= i) tag++;
        }
        if(tag == i) return i;
        tag = 0;
        swap(a[maxIndex], a[i]);
        maxIndex = 0;
    }
    return i;
}

template<class T>
int selectionSortBoolean(T *a, int n)
{
    int i;
    bool sorted = false;
    for(i = n-1; !sorted && (i >= 0); i--)
    {
        int maxIndex = 0;
        sorted = true;
        for(int j = 1; j <= i; j++)
        {
            if(a[j] >= a[maxIndex]) maxIndex = j;
            else sorted = false;
        }
        swap(a[maxIndex], a[i]);
    }
    return i;
}

int main()
{
    int a[] = {8, 7, 6, 5, 4, 3, 2, 1};
    int len = sizeof(a)/sizeof(a[0]);
    int times = 0;
    times = selectionSortBoolean(a, len);
    // for(int i = 0; i < len; i++)
    //     cout << a[i] << " ";
    // cout << endl << times;
}