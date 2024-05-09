//编写C++代码实现三个参数的模版函数accumulate。测试代码。
#include<iostream>
using namespace std;

template<class T>
T accumulate(T an[], T* tp, T initValue)
{
    for(int i = 0; i < tp-an; i++)
        initValue += an[i];
    return initValue;
}

int main()
{
    int a[] = {1, 2, 3, 4, 5};
    cout << accumulate<int>(a, a+5, 0);
}