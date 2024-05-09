//a[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0}
//使用及时终止选择排序进行排序
//对数组a[] = {8, 4, 5, 2, 1, 6, 7, 3, 0}重复一
#include"../../../MyTool.h"

template<class T>
void selectionSort_in_time(T a[], int n)
{
    bool sorted = false;
    // int indexOfMax = 0;
    int i;
    for(i = n-1; i >= 0 && !sorted; i--)
    {
          int indexOfMax = 0;
        sorted = true;
        for(int j = 0; j <= i; j++)
            if(a[j] >= a[indexOfMax])
                indexOfMax = j;
            else sorted = false;
        std::swap(a[i], a[indexOfMax]);
        // indexOfMax = 0;
    }
    std::cout << i << std::endl;
}

int main()
{
    int a[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    selectionSort_in_time<int>(a, GETSIZE(a));
    print_1D_array_incpp<int>(a, GETSIZE(a));
}

//9, 8, 7, 6, 5, 4, 3, 2, 1

//1, 8, 7, 6, 5, 4, 3, 2, 9
//1, 2, 7, 6, 5, 4, 3, 8, 9
//1, 2, 3, 6, 5, 4, 7, 8, 9
//1, 2, 3, 4, 5, 6, 7, 8, 9
//

