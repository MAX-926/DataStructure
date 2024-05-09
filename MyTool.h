#ifndef MYTOOL_H
#define MYTOOL_H
#include<stdio.h>
#include<iostream>
#include<string>
//确定数组长度
#define GETSIZE(x) (sizeof(x) / sizeof(*x))

// IllegalClass
class IllegalParameter
{
    public:
        IllegalParameter():message("illegal Parameter"){}
        IllegalParameter(const std::string& theMes):message(theMes){}
        void outputMessage(){std::cout << "Illgal information: " << message << std::endl;}
    private:
        std::string message;
};

template<class T>
void print_1D_array_incpp(T a[], int n)
{
    for(int i = 0; i < n; i++)
        std::cout << a[i] << " ";
}

//顺序打印一维数组
template<class T>
void print_1D_array(T *a, int len)
{
    int i;
    for(i = 0; i < len; i++)
    {
        printf("a[%d] = %d\n", i, a[i]);
    }
}

void print_1D_array_d(double* a, int len)
{
    int i;
    for(i = 0; i < len; i++)
    {
        printf("a[%d] = %lf\n", i, a[i]);
    }
}

//逆序存储一维数组
void swap_store_1D_array(int *a, int len)
{
    int tmp, i;
    for(i = 0; i < (int)len/2; i++)
    {
        tmp = a[i];
        a[i] = a[len-1-i];
        a[len-1-i] = tmp;
    }
}
//非下标法
void swap_store_1D_array1(int *x, int len)
{
    int i, tmp;
    for(i = 0; i < (int)len/2; i++)
    {
        tmp = *(x+i);
        *(x+i) = *(x+len-1-i);
        *(x+len-1-i) = tmp;
    }
}

//找出一个数组的最大值与最小值
int Max, Min;
void find_max_min(int a[], int len)
{
    Max = Min = a[0];
    int i;
    for(i = 0; i < len; i++)
    {
        if(a[i] > Max) {Max = a[i];continue;}
        if(a[i] < Min) Min = a[i];
    }
}

//打印rows*rows的二维数组
template<class T>
void print_2D_array(T **a, int rows)
{
    for(int i = 0; i < rows; i++)
    {
        print_1D_array_incpp<T>(a[i], rows);
        std::cout << std::endl;
    }
}

template<class T>
void print_2D_array(T **a, int rows, int columns)
{
    for(int i = 0; i < rows; i++)
    {
        print_1D_array_incpp<T>(a[i], columns);
        std::cout << std::endl;
    }
}

template<class T>
void create2DArray(T ** &a, int numberOfRows, int numberOfColumns)
{
    a = new T*[numberOfRows];
    for(int i = 0; i < numberOfRows; i++)
        a[i] = new T[numberOfColumns];
}


// template<class T>
// void create2DArray(T *** a, int numberOfRows, int numberOfColumns)
// {
//     *a = new T*[numberOfRows];
//     for(int i = 0; i < numberOfRows; i++)
//         (*a)[i] = new T[numberOfColumns];
// }


template<class T>
void init2DArray(T ** &a, int numberOfRows, T value)
{
    for(int i = 0; i < numberOfRows; i++)
        for(int j = 0; j < numberOfRows; j++)
            a[i][j] = value;
}

template<class T>
void init2DArray(T ** &a, int numberOfRows, int numberOfColumns, T value)
{
    for(int i = 0; i < numberOfRows; i++)
        for(int j = 0; j < numberOfColumns; j++)
            a[i][j] = value;
}

// template<class T>
// void init2DArray(T *** a, int numberOfRows, T value)
// {
//     for(int i = 0; i < numberOfRows; i++)
//         for(int j = 0; j < numberOfRows; j++)
//             (*a)[i][j] = value;
// }


unsigned long int factorial(int n)
{
    if(n <= 1) return 1;
    else return n*factorial(n-1);
}

#endif //MYTOOL_H