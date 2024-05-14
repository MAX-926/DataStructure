//squareMatrixMultiply
//确定两个n*n矩阵相乘时执行力多少次乘法
//共执行：n*n*n次乘法
#include"../../MyTool.h"
#include"22..cpp"

template<class T>
void mult(T ** &a, T ** &b, T ** &c, int numberOfRows)
{
    for(int i = 0; i < numberOfRows; i++)
        for(int j = 0;  j < numberOfRows; j++)
        {
            T sum = 0;
            for(int k = 0; k < numberOfRows; k++)
                sum += a[i][k] * b[k][j];
            c[i][j] = sum;
        }
}

template<class T>
void squareMatrixMultiply(T **&a, T **&b, T **&c,  int numberOfRows)
{
    for(int i = 0; i < numberOfRows; i++)
        for(int j = 0; j < numberOfRows; j++)
            c[i][j] = 0;
    // int count = 0;
    for(int i = 0; i < numberOfRows; i++)
        for(int k = 0; k < numberOfRows; k++)
        // for(int j = 0; j < numberOfRows; j++)
            for(int j = 0; j < numberOfRows; j++)
            // for(int k = 0; k < numberOfRows; k++)
            {
                c[i][j] += a[i][k]*b[k][j];
                // count++;
            }
            // std::cout << count << std::endl;

}

//squateMatrixMultiply_efficent
//减少了缓存未命中的情况
template<class T>
void squareMatrixMultiply_efficent(T **&a, T ** &b, T ** &c, int numberOfRows)
{
    for(int i = 0; i < numberOfRows; i++)
        for(int j = 0; j < numberOfRows; j++)
            for(int k = 0; k < numberOfRows; k++)
                c[i][k] += a[i][j]*b[j][k];
}

template<class T>
void squareMatrixMultiplyTrans(T **&a, T **&b, T **&c,  int numberOfRows)
{
    transpose(b, numberOfRows);
    for(int i = 0; i < numberOfRows; i++)
        for(int j = 0; j < numberOfRows; j++)
            for(int k = 0; k < numberOfRows; k++)
                c[i][j] += a[i][k]*b[j][k]; 
}

int main()
{
    int **a, **b, **c;
    int numberOfRows = 2;
    create2DArray<int>(a, numberOfRows, numberOfRows);
    create2DArray<int>(b, numberOfRows, numberOfRows);
    create2DArray<int>(c, numberOfRows, numberOfRows);
    init2DArray<int>(a, numberOfRows, 1);
    // init2DArray<int>(b, numberOfRows, 1);
    a[0][0] = 1;
    a[0][1] = 2;
    a[1][0] = 3;
    a[1][1] = 4;

    b[0][0] = 1;
    b[0][1] = 2;
    b[1][0] = 3;
    b[1][1] = 4;
    init2DArray<int>(c, numberOfRows, 0);
    squareMatrixMultiply<int>(a, b, c, numberOfRows);
    mult<int>(a, b, c, numberOfRows);
    print_2D_array<int>(c, numberOfRows);
}