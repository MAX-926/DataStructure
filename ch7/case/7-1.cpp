#include<iostream>
using namespace std;

int main()
{
    int numberOfRows = 5;

    //定义每一行的长度
    int length[5] = {6, 3, 4, 2, 7};

    //声明一个二维数组
    //且分配所需要的行数
    int** irregualrArray = new int*[numberOfRows];

    //分配每一行的空间
    for(int row = 0; row < numberOfRows; row++)
        irregualrArray[row] = new int[length[row]];

    //像使用规则数组一样使用不规则数组
    irregualrArray[2][3] = 5;
    irregualrArray[4][6] = 2;
    irregualrArray[1][1] = 3;

    //输出选择的数据元素
    std::cout << irregualrArray[2][3] << std::endl;
    std::cout << irregualrArray[4  ][6] << std::endl;
    std::cout << irregualrArray[1][1] << std::endl;

    return 0;
}