//matrix add
#include"../../../MyTool.h"
// typedef int** INT;

//执行加法次数：numberOfRows * numberOfColumns
template<class T>
void matrixAdd(T **a, T **b, T **c, int numberOfRows, int numberOfColumns)
{
    for(int i = 0; i < numberOfRows; i++)
        for(int j = 0; j < numberOfColumns; j++)
            c[i][j] = a[i][j] + b[i][j];
}

//引用传参的重要性
int main()
{
    int **a,** b,** c;
    create2DArray<int>(a, 2, 2);
    create2DArray<int>(b, 2, 2);
    create2DArray<int>(c, 2, 2);
    init2DArray<int>(a,2, 1);
    init2DArray<int>(b, 2, 2);
    init2DArray<int>(c, 2, 0);
    matrixAdd<int>(a, b, c, 2, 2);
    print_2D_array<int>(c, 2);
}

    // int **a;
    // a = new int*[2];
    // a[0] = new int[2];
    // a[1] = new int[2];
    // a[0][0] = 1;