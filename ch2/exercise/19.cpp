//递归就是不断用某种原子步骤解决问题的办法
#include"../../../MyTool.h"

template<class T>
T factorial(int n)
{
    if(n <=1) return 1;
    else return n*factorial<int>(n-1);//执行n-1次乘法
}

int main()
{
    std::cout << factorial<int>(5);
}