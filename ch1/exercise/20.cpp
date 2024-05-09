//1）编写递归程序计算斐波那契数（Fibonacci）Fn。测试你的代码
// 1 1 2 3 5 8 13 21

#include<iostream>
#include<string.h>
using namespace std;

// int Fibonacci(int n)
// {
//     //basic part
//     if(n == 1) return 1;
//     else if(n == 2) return 1;
//     else
//         return Fibonacci(n-1) + Fibonacci(n-2);
// }

//2)证明对于1）中编写的代码， 当计算Fn且n>2时， Fi的计算多于一次。
// int Fibonacci(int n, int* ip)
// {
//     //basic part
//     if(n == 1){(*ip)++; return 1;}
//     else if(n == 2){(*ip)++; return 1;}
//     else{
//         (*ip)++;
//         return Fibonacci(n-1, ip) + Fibonacci(n-2, ip);
//         }
// }

//3) 编写非递归函数计算斐波那契数（Fibonacci）Fn。对每一个斐波那契数，你的代码应该只计算一次。测试你的代码。
// int* Fibonacci(int *fp, int n)
// {
//     fp[0] = fp[1] = 1;
//     for(int i = 2; i < n; i++)
//     {
//         fp[i] = fp[i-1] + fp[i-2];
//     }
//     return fp;
// }

int main()
{   
    //2)
    // int i = 0;
    // int *ip = &i; 
    // cout << Fibonacci(4, ip) << endl;
    // cout << i;

    //3)
    // int *fp = new int[sizeof(int)*20];
    // memset(fp, 0, 20*sizeof(int));
    // for(int i = 0; i < 20; i++)
    //     cout << Fibonacci(fp, 20)[i] << " ";
}