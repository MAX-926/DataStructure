#include"12.cpp"//linkedStack
#include"../case/8-4.cpp"//arrayStack
#include"../case/derivedLinkedStack.cpp"//derivedLinkedStack
#include<time.h>
using namespace std;
//设计程序，10 000 000-操作序列比较 arrayStack, linkedStack ,derivedLinkedStack的性能

// int main()
// {
//     // linkedStack<int> ls;
//     arrayStack<int> ls;
//     for(int i = 0; i < 10000; i++)
//         ls.push(i);
//     for(int i = 0; i < 10000; i++)
//     {
//         cout << ls.top();
//         ls.pop();
//     }
// }

int main()
{
    // arrayStack<int> as;//初始容量10
    // linkedStack<int> as;
    derivedLinkedStack<int> as;
    double clocksPerMillions = (double)CLOCKS_PER_SEC / 1000;
    int loopTimes = 10;
    //打印提示信息
    //一次测试一个类型的数据
    cout << "class type" << "\t" << "initialCapacity:10\n";
    clock_t startTime = clock();
    //重复10次，取测量结果的平均值
    for(int i = 0; i < 1; i++)
    {
        for(int i = 0; i < 10000000; i++)
            as.push(i);
        // cout << as.size();
        for(int i = 0; i < 10000000; i++)
        {
            as.top();
            as.pop();
        }
    }
    clock_t endTime = clock();
    double totalTik = (double)(endTime - startTime);
    double average_time_cost = totalTik / loopTimes;
    average_time_cost /= clocksPerMillions;
    cout <<  "arrayStack" << "\t" << average_time_cost << endl;
    cout << "单位: ms" << endl;
}

// /*
// class           initialCapacity(10)
// arrayStack          250~280 ms
// linkedStack         17446.3 ms
// derivedLinkedStack  17274.2 ms

// */