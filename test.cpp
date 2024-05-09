// #include<iostream>
// using namespace std;

// int main()
// {
//     int a, b, c;
//     a = 2, b = 1, c = 0;
//     cout << a+b*c+b/c;
// }
#include"time.h"
#include<math.h>
#include"../MyTool.h"
#include<iostream>
#include<numeric>
#include<algorithm>
#include<iterator>
using namespace std;

template<class T>
T sum(T an[], int n)
{
    T theSum = 0;
    // for(int i = 0; i < n; i++)
    //     theSum += an[i];
    // return theSum;
    return accumulate(an, an+5, theSum);
}

template<class T>
T product(T an[], int n)
{
    T theProduct = 1;
    return accumulate(an, an+5, theProduct, multiplies<T>());
}

template<class T>
void permutation(T list[], int k, int m)
{
    do
    {
    copy(list, list+m+1, ostream_iterator<T>(cout, " "));
    cout << endl;
    // for(int i = 0; i < 5; i++)
    //     cout << list[i] << " ";
    }while(next_permutation(list, list+m+1));
}

int main()
{
    // int an[] = {1, 2, 3, 4, 5};
    // // cout << product<int>(an, 5);
    // permutation<int>(an, 0, 4);
    // cout << endl;
    // // for(int i = 0; i < 5; i++)
    // //     cout << an[i] << " ";

//    cout <<  factorial(32);
    // double n = 10;
    // for( ;!(pow(2, n)/n < 100); n-= 0.01);
    // cout << (pow(2, 14)/14  );
    // cout << n;

    clock_t elapsedTime;
    clock_t aTime = clock();
    cout << aTime << endl << clock()-aTime << endl;
    aTime = clock();
    cout << aTime << endl << clock()-aTime << endl;
}