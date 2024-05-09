#include<iostream>
#include<math.h>
using namespace std;

void outputRoots(const double& a, const double& b, const double& c)
{//计算和输出二次方程的根
    // if(a == 0) return;
    double d = b*b-4*a*c;
    if(d > 0)
    {
        double sqrtd = sqrt(d);
        cout << "there are two real roots:"
             << (-b + sqrtd)/(2*a) << " and "
             << (-b - sqrtd)/(2*a) << endl;
    }
    else if(d == 0)
    {
        cout << "there is only one distinct root "
             << -b/(2*a)
             << endl;
    }
    else//复数共轭根
    {
        cout << "The roots are complex"
             << endl
             << "The real part is "
             << -b/(2*a)
             << endl
             << "The imaginary part is "
             << sqrt(-d)/(2*a) << endl;
    }
}

int main()
{
    outputRoots(1, -5, 6);
    return 0;
}