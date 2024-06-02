#include"30.cpp"
#include<iostream>
using namespace std;

template<class T>
void nonMember_reverse(circularListWithReverse<T> &CLWR)//相比直接调用成员函数进行链表倒序， 多了一个外层函数调用的开销，会传递一个链表对象的引用进入外层函数
{
    CLWR.reverse();
}

int main()
{
    circularListWithReverse<int> x;
    for(int i = 0; i < 10; i++)
        x.insert(i, i+1);
    cout << x << endl;
    nonMember_reverse(x);
    cout << x << endl;
}