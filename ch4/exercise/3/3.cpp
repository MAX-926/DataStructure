#include"E:\DataStructure\MyTool.h"
#include<time.h>
#include<fstream>

using namespace std;
//冒泡排序2-9

template<class T>
void buble(T a[], int n)
{
    for(int i = 1; i < n; i++)
        if(a[i] < a[i-1])
            swap(a[i], a[i-1]);
}

template<class T>
void bubleSort(T a[], int n)
{
    int i;
    for(i = n; i > 1; i--)
        buble<T>(a, i);
    // of << i << endl;
}

//及时终止的冒泡排序2-13

template<class T>
void bubleSort_inTime(T a[], int n)
{
    //
    bool sorted = false;
    int i;
    for(i = n; i > 1 && !sorted; i--)
    {
        sorted = true;
        for(int j = 1; j < i; j++)
            if(a[j] < a[j-1]) 
            {
                swap(a[j], a[j-1]);
                sorted = false;
            }
    }
    // of << i << endl;
}

int main() 
{
    // coutstream of("output2_inline.txt");
    //测试insertionSort
    //使用clock()进行计时
    //设定实例特征值
    ofstream of("3_output.txt");
    int a[1000], step = 10;
    double clocksPerMillis = (double)(CLOCKS_PER_SEC) / 1000;
    of << "The worst-case time, in milliseconds, are" << endl;
    of << "n \tRepetions \telapsedTime \tTime per sort\n ";
    for(int n = 0; n <= 1000; n+=step)
    {
        // clock_t elapsedTime = 0;
        long numbercoutRepetions = 0;
        clock_t startTime = clock();
        do
        {
            numbercoutRepetions++;
        //为每一个实例特征值设计最坏情况下的测试数据
            for(int i = 0; i < n; i++)
                a[i] = n-i;
            bubleSort<int>(a, n);
        }while((clock() - startTime) < 1000);
        double elapsedTime = (clock()-startTime) / clocksPerMillis;
        of << n << '\t' << numbercoutRepetions << '\t' << elapsedTime/clocksPerMillis << '\t' << elapsedTime/clocksPerMillis/numbercoutRepetions << endl;
        if(n == 100) step = 100;
    }
    return 0;

//    int a[] = {1, 2, 3};
//    bubleSort<int>(a, GETSIZE(a));
//    print_1D_array_incpp<int>(a, GETSIZE( a));
}