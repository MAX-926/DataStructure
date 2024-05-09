//[最大公约数(Greatest Common Divisor, GCD)] 当两个非负整数x和y都是0的时候， 

//gcd(20, 30) = gcd(30, 20) = gcd(20, 10) = gcd(10, 0) = 10
//gcd(112, 42) = gcd(42, 28) = gcd(28, 14) = gcd(14, 0) = 14


#include<iostream>
using namespace std;

unsigned int gcd(unsigned int x, unsigned int y)
{
    if(y == 0) return x;
    else return gcd(y, x % y);
}

unsigned int dgcd(unsigned int a, unsigned int b)
{
    if(b == 0) return a;
    else 
    {
        if(a > b)
        return dgcd(b, a-b);
        else return dgcd(a, b-a);
    }
}

int main()
{
    cout << dgcd(42, 112);
}