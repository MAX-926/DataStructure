//[阿克曼函数Ackermann's Function] 公式（1-5）定义的是阿克曼函数。其中，i和j是大于等于1的整数。
//A(i, j) = 2^j (i = 1和 j>=1), A(i-1, 2) (i>=2, j = 1), A(i-1, A(i, j-1)) (i, j >=2)
//1)使用公式(1-5)手算A(1， 2)， A(2, 1)和A(2, 2)

//A(1, 2) = 2^2 = 4, A(2, 1) = A(1, 2) = 4, A(2, 2) = A(1, A(2, 1)) = A(1, 4) = 2^4 = 16

//2)确定函数定义中的基础部分和递归部分。

//基础部分：A(i, j) = 2^j (i = 1和j >= 1)
//递归部分：A(i-1, 2) (i>=2, j = 1), A(i-1, A(i, j-1)) (i, j >=2)

//3)编写C++递归函数计算A(i, j)。测试你的代码。

#include<iostream>
#include<math.h>
using namespace std;

double Ackermanns(unsigned int i, unsigned int j)
{
    if(i == 1 && j >= 1) return pow(2, j);
    if(i >= 2 && j == 1) return Ackermanns(i-1, 2);
    if(i >= 2 &&j >= 2) return Ackermanns(i-1, Ackermanns(i, j-1));
    return 0;
}

int main()
{
    cout << Ackermanns(1, 2);
}