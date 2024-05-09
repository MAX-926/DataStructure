//考察在下面的公式（1-4）中定义的函数f，其中n是非负整数。
// F(n) = n/2(n是偶数) 、F(3n+1)(n是奇数)
//1)使用公式手算F(5)和F(7)
//F(5) = F(3*5+1) = F(16) = 16/2 = 8
//F(7) = F(3*7+1) = F(22) = 22/2 = 11

//2)确定函数的基础部分和递归部分。证明重复应用递归部分可以把等式右侧的f表达式转为基础部分。

//基础部分f(n) = n/2,递归部分f(n) = f(3n+1) = 3*(n/2) + 1/2

//3)编写一个C++递归函数计算F(n)。测试你的代码。

#include<iostream>
using namespace std;

// double f(unsigned int n)
// {
//     if(n % 2 == 0) return n/2;
//     else return f(3*n+1);//3*f(n+1) - 1;
// }

// int main()
// {   
//     cout << f(5);
// }

//4)使用2)的证明编写C++非递归函数计算F(n)，不能使用循环。测试你的代码。
double f(unsigned int n)
{
    if(n % 2 == 0) return n/2;
    else return (3*n+1)/2;
}

int main()
{
    cout << f(5);
}