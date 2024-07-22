//compare the performance about arrayQueue and slowArrayQueue
//预期：arrayQueue会比slowArrayQueue表现好
//因为在扩容的触发条件上，slowArray在未完全利用数组空间的情况下就需要移动队列元素；而arrayQueue是环形队列，对数组空间的利用率很高（除去需要占用数组一个空间表示queueFront的信息）

#include"6.cpp"
#include"../case/9-2.cpp"
#include<time.h>//利用滴答数计时
#include<iostream>
const int n = 1000000;

using namespace std;

int main()
{//设置一个性能比较程序：
//比较序列：n次push(), n次front()接上pop();
    double clocksPerMillions = CLOCKS_PER_SEC / 1000;//把程序的执行时间从s转换为ms
    long loopTimes = 0;
    arrayQueue<int> aq;//initialCapacity = 10
    slowArrayQueue<int> saq;//initialCapacity = 10
    //打印提示信息：
    cout << "scale:" << n << '\t' << "time cost:\n";
    clock_t start = clock();
    do
    {
    loopTimes++;
    //初始化数据

    //执行动作序列
    //n次push
    for(int i = 0; i < n; i++)
        // aq.push(i);
        saq.push(i);
    //n次front和pop
    for(int i = 0; i < n; i++)
    {
        // aq.front();
        // aq.pop();
        saq.front();
        saq.pop();
    }
    }while(((double)(clock() - start))/clocksPerMillions <= 10000);//若误差为1s，则这个循环将误差控制在1/1000内
    // cout << ((double)(clock() - start)) / clocksPerMillions/loopTimes;
    double timeCost = ((double)(clock() - start)) / clocksPerMillions / loopTimes;//得到单次动作序列的用时
    cout << n << "\t\t" <<  timeCost << endl;
}

/*
arrayQueue:
scale:5000      time cost:
5000            0.197633

scale:1000000   time cost:
1000000         32.8721

slawArrayQueue:
scale:5000      time cost:
5000            0.0976288

cale:1000000   time cost:
1000000         15.5342
*/