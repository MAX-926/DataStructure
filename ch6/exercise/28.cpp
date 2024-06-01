//测试程序6-3和程序6-13的indexOf在最坏和平均情况下的时间性能

#include"../case/6-2.h"
#include"../case/6-13.h"
#include<time.h>
#include<fstream>

using namespace std;

int main()
{
    // circularListWithHeader<int> x;
    chain<int> y;
    ofstream out;
    out.open("28_output.txt", ios::app);
    time_t clocksPerMillis = CLOCKS_PER_SEC / 1000;
    int numsOfRepetions = 0;
    int inflateExp = 10;
    cout << "N" << '\t' << "clocks" << '\t' << "Time cost per search" << endl;
    // out << "N" << '\t' << "clocks" << '\t' << "Time cost per search" << endl;
    for(int n = 100; n <= 100000; n*=inflateExp)
    {
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
    out.close();
    // circularListWithHeader<int> x;
    // for(int i = 0; i < 10; i++)
    //     x.insert(i, i);
    // cout << x << endl;
}

// circularListWithHeader::indexOf
// N       clocks  Time cost per search
// 100     1000    0.215054
// 1000    1010    15.303
// 10000   1023    1023
// 100000  46795   46795

// chain::indexOf
// N       clocks  Time cost per search
// 100     1000    0.029976
// 1000    1000    1.81818
// 10000   1014    253.5
// 100000  26729   26729