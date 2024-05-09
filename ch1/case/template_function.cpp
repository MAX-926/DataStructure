#include<iostream>
using namespace std;

// template<class T>
// T abc(T a, T b, T c)
// {
//     return a + b * c;
// }

// template<class T>
// T abc(T& a, T& b, T& c)
// {
//     return a + b * c;
// }

int abc(int a, int b, int c)
{
    return a + b * c;
}

float abc(float a, float b, float c)
{
    return a + b * c;
}

int main()
{
    // int ra;
    // float rb;
    // double rc;
    // ra = abc<int>(1.2, 5, 2.4);
    // rb = abc<float>(1.2, 5, 2.4);
    // rc = abc<double>(1.2, 5, 2.4);
    // cout << ra << " " << rb << " " << rc;
    
    cout << abc(1, 2, 3.0);
}