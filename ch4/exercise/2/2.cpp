#include"../../../MyTool.h"
//利用程序4-2，对程序2-14和程序2-15的两个插入排序版本， 测量在最坏情况下的运行时间。使用程序4-2的n值。试比较两种插入排序方法的优点。

//插入排序
//2-14
//优点：函数功能逻辑清晰，层次分明，可读性佳
template<class T>
void insert(T a[], int n, const T &x)
{
    int i;
    for(i = n-1; i >= 0 && a[i] > x; i--)
        a[i+1] = a[i];
    a[i+1] = x;
}

template<class T>
void insertionSort(T a[], int n)
{
    for(int i = 1; i < n; i++)
    {
        T tmp = a[i];
        insert(a, i, tmp);//多了参数压栈，断口地址保存
    }
}

//2-15
//对insert函数内联处理
//优点：函数体内没有函数调用，省去了保存局部变量、函数断口地址等等的空间开销
template<class T>
void insertionSort_inline(T a[], int n)
{
    //
    for(int i = 1; i < n; i++)
    {
        int j;
        T tmp = a[i];
        for(j = i-1; j >= 0 && tmp < a[j]; j--)
            a[j+1] = a[j];
        a[j+1] = tmp;
    }
}

// #include<iostream>
#include<time.h>
#include<fstream>
using namespace std;
//程序4-2:控制测量误差时间在10%内
int main()
{
    ofstream of("output2_inline.txt");
    //测试insertionSort
    //使用clock()进行计时
    //设定实例特征值
    int a[1000], step = 10;
    double clocksPerMillis = (double)(CLOCKS_PER_SEC) / 1000;
    of << "The worst-case time, in milliseconds, are" << endl;
    of << "n \tRepetions \telapsedTime \tTime per sort\n ";
    for(int n = 0; n <= 1000; n+=step)
    {
        // clock_t elapsedTime = 0;
        long numberOfRepetions = 0;
        clock_t startTime = clock();
        do
        {
            numberOfRepetions++;
        //为每一个实例特征值设计最坏情况下的测试数据
            for(int i = 0; i < n; i++)
                a[i] = n-i;
            insertionSort_inline<int>(a, n);
        }while((clock() - startTime) < 1000);
        double elapsedTime = (clock()-startTime) / clocksPerMillis;
        of << n << '\t' << numberOfRepetions << '\t' << elapsedTime/clocksPerMillis << '\t' << elapsedTime/clocksPerMillis/numberOfRepetions << endl;
        if(n == 100) step = 100;
    }
    return 0;
}