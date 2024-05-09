// #include<iostream>
// using namespace std;

// int factorial(int n)
// {
//     if(n <= 1) return 1;
//     for(int i = n-1; i > 1; i--)
//         n *= i;
//     return n;
// }

// int main()
// {
//     cout << factorial(3);
// }

#include<iostream>
using namespace std;

// c0 + c1x + c2x2 ...

template<class T>
T polyEvalue(T coeff[], int n, const T &x)
{
    T y = 1 ,value = coeff[0];
    for(int i = 1; i < n; i++)
    {
        y *= x;
        value += y*coeff[i];
    }
    return value;
}

template<class T>
T horner(T coeff[], int n, const T &x)
{
    // T value = coeff[n-1]*x + coeff[n-2];    
    // for(int i = n-3; i >= 0; i--)
    // {
    //     value = value*x + coeff[i];
    // }
    T value1 = coeff[n];
    for(int i = n-1; i >= 0; i--)
        value1 = value1*x + coeff[i];
    return value1;
}

int main()
{
    int coeff[] = {1, 2, 3};
    // cout << polyEvalue<int>(coeff, 3, 2);//1 + 2*x + 3*x*x
    cout << horner<int>(coeff, 2, 2);//1 + 2*x + 3*x*x
}