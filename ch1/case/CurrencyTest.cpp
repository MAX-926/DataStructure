#include<iostream>
#include"Currency(c).h"
// #include"myExceptions.h"

using namespace std;

int main()
{
    Currency<char> g, h('+', 3, 50), i, j;

    // 使用两种形式的setValue来赋值
    g.setValue('-', 2, 25);
    i.setValue(-6.45);

    //调用成员函数add和output
    j = h.add(g);
    h.output(); // 1.25
    cout << '+';
    g.output();
    cout << '=';
    j.output(); cout << endl;

    // 连续调用两次成员函数add
    j = i.add(g).add(h);
        // 省略了输出语句
    
    // 调用成员函数increment和add
    j = i.increment(g).add(h);
        // 省略了输出语句
    
    // 测试异常
    cout << "Attempting to initialize with cents = 152" << endl;
    try{i.setValue('+', 3, 152);}
    catch(illegalParameterValue e)
    {
        cout << "Caught thrown exception" << endl;
        e.outputMessage();
        // return 1;
    }
    // cout << "\ni am here";
}