//transpose（见程序2-19）共执行了多少次交换

#include"../../../MyTool.h"

//交换次数：Rows*(Rows-1)/2
template<class T>
void transpose(T ** &a, int numberOfRows)
{
    for(int i = 0; i < numberOfRows; i++)
        for(int j = i+1; j < numberOfRows; j++)
            std::swap(a[i][j], a[j][i]);
}

// int main()
// {
//     int **a;
//     create2DArray<int>(a, 3, 3);
//     int c = 0;
//     for(int i = 0; i < 3; i++)
//         for(int j = 0; j < 3; j++)
//         {
//             a[i][j] = c;
//             c++;
//         }
//     print_2D_array<int>(a, 3);
//     std::cout << std::endl;
//     transpose<int>(a, 3);
//     print_2D_array<int>(a, 3);
// }