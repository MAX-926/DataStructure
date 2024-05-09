#include<iostream>
using namespace std;

int factorial(int n)
{
    if(n <=0) return 1;
    int re = 1;
    for(int i = 1; i <= n; i++)
        re *= i;
    return re;
}

int main()
{
    cout << factorial(-1);
}
