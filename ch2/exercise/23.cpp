//squareMatrixMultiply
//确定两个n*n矩阵相乘时执行力多少次乘法
//共执行：n*n*n次乘法
#include"../../../MyTool.h"
#include"22..cpp"

template<class T>
void squareMatrixMultiply(T **&a, T **&b, T **&c,  int numberOfRows)
{
    int count = 0;
    for(int i = 0; i < numberOfRows; i++)
        for(int j = 0; j < numberOfRows; j++)
            for(int k = 0; k < numberOfRows; k++)
            {
                c[i][j] += a[i][k]*b[k][j];
                count++;
            }
            std::cout << count << std::endl;
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
    init2DArray<int>(b, numberOfRows, 1);
    // b[0][0] = 1;
    // b[0][1] = 2;
    // b[1][0] = 3;
    // b[1][1] = 4;
    init2DArray<int>(c, numberOfRows, 0);
    // squareMatrixMultiplyTrans<int>(a, b, c, numberOfRows);
    squareMatrixMultiply<int>(a, b, c, numberOfRows);
    print_2D_array<int>(c, numberOfRows);
}