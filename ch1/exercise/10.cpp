#include<iostream>
using namespace std;

int abc(int a, int b, int c)
{
    if(a < 0 && b < 0 && c < 0) throw 1;
    if(a ==  b == c == 0) throw 2;
    return a + b * c;
}

int main()
{
    try
    {
        cout << abc(0, 0, 0) << endl;
    }
    catch(int e)
    {
        if(e == 1) {cout << "a, b and c were < 0" << endl; cout << e << endl; return 1;}   
        if(e == 2) {cout << "a, b and c were all = 0" << endl; cout << e << endl; return 1;}   
    }
    return 0;
}