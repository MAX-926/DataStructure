//a File use to test cpp program performance
// #include"../case/5-3.h"
#include<iostream>
#include<time.h>

int main()
{
    double clocksPerMillis = CLOCKS_PER_SEC / 1000;
    int step = 10;
    for(int n = 0; n <= 1000; n += step)
    {
        double numbersOfRepetions = 0;
        clock_t startTime = clock();
        do
        {
            //functions acativities
        }while(clock() - startTime < 1000);
        // 處理測試結果
        double elapsedTime = (double)clock() - startTime;
        std::cout << n << '\t' << elapsedTime << '\t' << elapsedTime/clocksPerMillis/numbersOfRepetions << std::endl;
    }
}