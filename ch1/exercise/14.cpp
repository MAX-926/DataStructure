#include<iostream>
#include"E:\thinking in C++\DataStructor\Tool.h"
using namespace std;

template<class T>
void changeLength2D(T ** &x,  int numberOfRows, int numberOfColumns, T** &y, int newRows, int rowSize[])
{
    make2dArray_wideUse(y, newRows, rowSize);
    for(int i = 0; i < (newRows > numberOfRows?numberOfRows:newRows); i++)
        for(int j = 0; j < (rowSize[i] > numberOfColumns?numberOfColumns:rowSize[i]); j++)
            y[i][j] = x[i][j];
    delete2dArray(x, numberOfRows, numberOfColumns);
}

int main()
{
    int ** x, ** y;
    int rowSize[] = {1, 2, 3, 4, 5};
    make2dArray(x, 3, 2);
    x[0][0] = 0;
    x[0][1] = 1;
    x[1][0] = 2;
    x[1][1] = 3;
    x[2][0] = 4;
    x[2][1] = 5;
    // int ro[] = {2, 2, 2, 2, 2};
    // output_2DArray_wideUse(x, 3, ro);
    changeLength2D(x, 3, 2, y, 5, rowSize);
    output_2DArray_wideUse(y, 5, rowSize);
}