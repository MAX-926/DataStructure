//原地rows*rows矩阵转置
// [1， 2， 3 ]->    [1]
//                  [2]
//                  [3]
#include<iostream>
#include"../../../MyTool.h"

//从外层循环逐步向内层分析，要注意跳出循环需要的“一步”
template<class T>
void transpose(T **a, unsigned int rows)
{                               // s/e fre total_step
    for(int i = 0; i < rows; i++)// 1 rows+1 rows+1
        for(int j = rows-1; j >= i; j--)//1 rows/2*(rows+1) rows/2*(rows+1)
            std::swap(a[i][j], a[j][i]);//1 rows/2*(rows-1) rows/2*(rows-1)
}

int main()
{
    // int a[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int **imp = new int*[3];
    for(int i = 0; i < 3 ;i++)
        imp[i] = new int[3];
    imp[0][0] = 1;
    imp[0][1] = 2;
    imp[0][2] = 3;
    imp[1][0] = 4;
    imp[1][1] = 5;
    imp[1][2] = 6;
    imp[2][0] = 7;
    imp[2][1] = 8;
    imp[2][2] = 9;
    transpose<int>(imp, 3);
    print_2D_array<int>(imp, 3);
}
