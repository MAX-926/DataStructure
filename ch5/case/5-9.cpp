//迭代器是指针，能够寻访数据结构
//5-9 使用数组迭代器
#include<iostream>
int main()
{
    int x[3] = {0, 1, 2};
    for(int *y = x; y < x+3; y++)
        std::cout << *y << " ";
    return 0;
}