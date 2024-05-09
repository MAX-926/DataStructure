//试确定函数matrixMultiply(见程序2-23)在实现一个m*n矩阵与一个n*p矩阵相乘时执行了多少次乘法？
//一共执行m*n*p次乘法
#include"../../../MyTool.h"

template<class T>
void matrixMultiply(T **&a, T **&b, T **&c, int m, int n, int p)
{
    //变m*p
    for(int i = 0; i < m; i++)
        for(int j = 0; j < p; j++)
            for(int k = 0; k < n; k++)
                c[i][j] += a[i][k] * b[k][j];
}

int main()
{
    int **a, **b, **c;
    int m = 2, n = 3, p = 2;
    create2DArray<int>(a, m, n);
    create2DArray<int>(b, n, p);
    create2DArray<int>(c, m, p);
    init2DArray<int>(a, m, n, 2);
    init2DArray<int>(b, n, p, 3);
    init2DArray<int>(c, m, p, 0);
    matrixMultiply<int>(a, b, c, m, n, p);
    print_2D_array<int>(c, m, p);
}