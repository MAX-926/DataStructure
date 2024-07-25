//利用百万级的操作序列（100w次push和100w次pop）比较arrayQueue和linkedQueue的性能

#include"../case/9-2.cpp"
#include"../case/linkedQueue.cpp"
#include<time.h>
#include<iostream>

using namespace std;

int main()
{
    arrayQueue<int> aq;
    linkedQueue<int> lq;

    time_t start = clock();
    double clocksPerMillions = CLOCKS_PER_SEC / 1000;
    long loopTimes = 0;

    // do
    // {
        loopTimes++;
        for(int i = 0; i < 1000000; i++)
            aq.push(i);
            // lq.push(i);
        for(int i = 0; i < 1000000; i++)
            aq.pop();
            // lq.pop();
    // }while(clock() - start >= 1000);
    time_t end = clock();
    double timeCost = (double)(end - start);
    timeCost = timeCost/clocksPerMillions/loopTimes;//得到序列的执行时间，以毫秒为单位
    cout << "timeCost = " << timeCost << endl;
}

/*
arrayQueue:
timeCost:40~50 ms

linkedQueue:
timeCost = 129156
timeCost = 120803

差异：同样的百万级操作序列，linkedQueue的时间开销大约是arrayQueue的2685倍
*/