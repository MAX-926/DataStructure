#include<iostream>
#include"CurrencyOverload.h"

using namespace std;

int main()
{
    Currency<char> g, h('-', 3, 50), i, j;

    // 使用两种形式的setValue来赋值
    g.setValue('-', 2, 25);
    i.setValue(-6.45);

    // 调用成员函数add和output
    j = h + g;
    cout << h << "+" << g << "=" << j << endl;

    // 连续两次调用成员函数add
    j = i + g + h;
    cout << i << "+" << g << "+"
         << h << "=" << j << endl;
    
    // 调用成员函数increment和add
    cout << "Increment " << i << "by" << g
         << " and then add " << h << endl;
    j = (i += g) + h;
    cout << "Result is " << j << endl;
    cout << "Increment object is " << i << endl;

    // 测试1异常
    cout << "Attempting to initialize with cents = 152" << endl;
    try{i.setValue('+', 3, 152);}
    catch(illegalParameterValue e)
    {
        cout << "Caught thrown exception" << endl;
        e.outputMessage();
    }
    return 0;
}