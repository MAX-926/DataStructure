#include"../../../MyTool.h"

//对insertionSort进行测试


//insert operation
template<class T>
void insert(T a[], int n, const T &x)
{
    int i;
    for(i = n-1; i >= 0 && a[i] > x; i--)
        a[i+1] = a[i];
    a[i+1] = x;
}


//insertionSort
template<class T>
void insertionSort(T a[], int n)
{
    //insertion
    for(int i = 1; i < n; i++)
    {
        T tmp = a[i];
        insert(a, i, tmp);
    }
}

#include<time.h>//包含性能测试工具clock()的库
using namespace std;

#include<fstream>

int main()
{
    //测试insertionSort函数
    // int a[] = {5, 4, 3, 2, 1, 0, 8, 9};
    // insertionSort<int>(a, GETSIZE(a));
    // print_1D_array_incpp<int>(a, GETSIZE(a));

    // //对insertionSort函数进行性能测量：
    // int a[1000], step = 10;
    // double clocksPerMillis = (double)(CLOCKS_PER_SEC) / 1000;//得到每毫秒的时钟滴答数

    // cout << "The wrost-case time, in milliseconds, are" << endl;
    // cout << "n \t Time" << endl;

    // // 次数n = 0, 10, 20, ..., 100, 200, 300, ..., 1000
    // for(int n = 0; n <= 1000; n += step)
    // {
    //     //用最坏测试数据初始化
    //     for(int i = 0; i < n; i++)
    //         a[i] = n-i;
    //     clock_t startTime = clock();
    //     insertionSort(a, n);
    //     double elapsedMillis = (clock() - startTime) / clocksPerMillis;

    //     cout << n << '\t' << elapsedMillis << endl;

    //     if(n == 100) step = 100;
    // }
    // return 0;
    ofstream off("4-1.1.txt");
    int a[1000], step = 10;
    double clocksPerMillis = (double)(CLOCKS_PER_SEC) / 1000;
    off << "The worst-case time, in milliseconds, are" << endl << "n \tRepetions \t Total Ticks \tTime per sort" << endl;
    // cout << "The worst-case time, in milliseconds, are" << endl;
    // cout << "n \tRepetions \t Total Ticks \tTime per sort" << endl;
    for(int n = 0; n <= 1000; n += step)
    {
        // double sumTime = 0;
        int numberOfRepetions = 0;
        clock_t startTime = clock();
        do
        {
        //初始化测试数据
        for(int i = 0; i < n; i++)
            a[i] = n-i;
        
        //排序测试
        // insertionSort(a, n);
        // double elapsedMillis = (clock() - startTime) / clocksPerMillis;
        // sumTime += elapsedMillis;
        numberOfRepetions++;
        if(n == 100) step = 100;
        }while(clock() - startTime < 1000);
        double elapsedMillis = (clock() - startTime) / clocksPerMillis;
        // elapsedMillis /= numberOfRepetions;
        off << n << " \t" << numberOfRepetions << " \t" << elapsedMillis
              << " \t" << elapsedMillis / numberOfRepetions
              << endl;
        // cout << n << '\t' << numberOfRepetions << '\t' << elapsedMillis*numberOfRepetions*clocksPerMillis << '\t' << elapsedMillis << endl;
        // cout << n << " \t" << numberOfRepetions << " \t" << elapsedMillis
        //       << " \t" << elapsedMillis / numberOfRepetions
        //       << endl;
        if(n == 100) step = 100;
    }
    off.close();
    return 0;
}