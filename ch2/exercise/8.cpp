//计算3x^4 + 4x^3 + 5x^2 + 6x + 7
//利用程序2-3与2-4
//把加法、乘法、操作数一一表示出来

//2-3
#include"../../../MyTool.h"
#include<fstream>

template<class T>
T polyEval(T coeff[], int n, const T &x)
{
    T result = coeff[n-1];
    std::cout << result << std::endl;
    T var = 1;
    for(int i = n-2; i >= 0;  i--)
    {
        var *= x;
        result += coeff[i]*var;
        std::cout << var << "*" << coeff[i] << std::endl;
    }
    return result;
}
//3x^2 + 2x + 1 = 1 + x(2 + 3x)
template<class T>
T horner(T coeff[], int n, const T &x)
{
    T term = coeff[0];
    T tmp;
    for(int i = 1; i < n; i++)
    {
        tmp = term;
        term = term * x + coeff[i];
        std::cout << tmp << "*" << x  << "+" << coeff[i] << std::endl;
    }
    return term;
}

int main()
{
    int coeff[] = {3, 4, 5, 6, 7};
    std::cout << polyEval<int>(coeff, GETSIZE(coeff), 2) << std::endl;
    std::cout << horner<int>(coeff, GETSIZE(coeff), 2);
}