//测试程序6-3和程序6-13的indexOf在最坏和平均情况下的时间性能

#include"../case/6-2.h"
#include"../case/6-13.h"
#include<time.h>
#include<fstream>

using namespace std;

int main()
{
    ofstream out;
    // out.open("28_output.txt", ios::app);
    time_t clocksPerMillis = CLOCKS_PER_SEC / 1000;
    int numsOfRepetions = 0;
    int inflateExp = 10;
    cout << "N" << '\t' << "clocks" << '\t' << "Time cost per search" << endl;
    // out << "N" << '\t' << "clocks" << '\t' << "Time cost per search" << endl;
    for(int n = 100; n <= 100000; n*=inflateExp)
    {
        // circularListWithHeader<int> x;
        chain<int> y;
        numsOfRepetions = 0;
        clock_t startTime = clock();
        do
        {
            ++numsOfRepetions;
            for(int k = 0; k < n; k++)
                y.insert(k, k+1);
                // x.insert(k, k+1);
            // x.indexOf(n+1);
            y.indexOf(n);
        }while(clock()-startTime < 1000);
        double elapsedTime = (double)clock() - startTime;
        cout << n << '\t' << elapsedTime << '\t' << elapsedTime/clocksPerMillis/numsOfRepetions << endl;
        // out << n << '\t' << elapsedTime << '\t' << elapsedTime/clocksPerMillis/numsOfRepetions << endl;
    }
    // out.close();
    // circularListWithHeader<int> x;
    // for(int i = 0; i < 10; i++)
    //     x.insert(i, i);
    // cout << x << endl;
}

// circularListWithHeader::indexOf
// N       clocks  Time cost per search
// 100     1001    0.810526
// 1000    1003    4.91667
// 10000   1159    289.75
// 100000  45707   45707

// chain::indexOf
// N       clocks  Time cost per search
// 100     1000    0.0297327
// 1000    1002    2.16883
// 10000   1079    269.75
// 100000  37900   37900

// int main()
// {
//     circularListWithHeader<int> x;
//     for(int i = 0; i < 10; i++)
//         x.insert(i, i+1);
//     x.insert(-1, 26);
//     cout << x << endl;
// }