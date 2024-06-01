#include"6-13.h"
#include<iostream>
using namespace std;
int main()
{
    // chainNode<int>* xp = new chainNode<int>(1, nullptr);
    // std::cout << xp->element;
    // chain<int> c, c1;
    // for(int i = 0; i < 5; i++)
    //     c.insert(i, i+1);
    // c1 = c;
    // std::cout << c << std::endl;
    // c.insert(4, 26);
    // std::cout << c;
    // cout << c1;
    circularListWithHeader<int> x;
    for(int i = 0; i < 10; i++)
        x.insert(i, i+1);
    cout << x << endl;
    x.erase(0);
    cout << x << endl;
    x.insert(0, 1);
    cout << x << endl;
}