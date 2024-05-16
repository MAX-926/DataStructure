//Reverse 原地颠倒线性表元素的顺序
#include"../case/5-3.h"
#include<time.h>
template<class T>
class arrayListWithReverse:public arrayList<T>
{
    public:
        arrayListWithReverse(int initialCapacity = 10):arrayList<T>(initialCapacity){}
        void reverse();
};

template<class T>
void arrayListWithReverse<T>::reverse()
{
    for(int i = 0; i < (this->listSize)>>1; i++ )
        std::swap((this->element)[i], (this->element)[(this->listSize) - i-1]);
}

template<class T>
void func(arrayListWithReverse<T> &x)
{
    x.reverse();
}

int main()
{
    double clocksPerMillis =(double) CLOCKS_PER_SEC / 1000;
    int step = 4000;
    // std::cout << "increRate" << std::endl;
    std::cout << "Scale" << '\t' << "elapsedTime" << '\t' << "Time per reverse" << std::endl;
    // double re[19];
    // int reIndex = 0;
    for(int n = 1000; n <= 10000; n += step)
    {
        double numberOfRepetions = 0;
        clock_t startTime = clock();
        do
        {
            numberOfRepetions++;
            arrayListWithReverse<int> x(n);
            for(int i = 0; i < n; i++)
                x.insert(i, i+1);
            // std::cout << x << std::endl;
            // x.reverse();
            func(x);
            // std::cout << x << std::endl;
        }while(clock() - startTime < 1000);
        clock_t elapsedTime = clock() - startTime;
        // re[reIndex++] = elapsedTime/clocksPerMillis/numberOfRepetions;    
        std::cout << n << '\t' << elapsedTime << '\t' << elapsedTime/clocksPerMillis/numberOfRepetions << std::endl;
        if(n == 5000) {step = 5000;}
    }

    // for(int i = 1; i < 19; i++)
    // {
    //     int delta = 10;
    //     if(i < 10)
    //     {
    //         std::cout << (re[i] - re[i-1])/delta << std::endl;
    //     }
    //     else
    //     {
    //         delta = 100;
    //         std::cout << (re[i] - re[i-1])/delta << std::endl;
    //     }
    // }
    // arrayListWithReverse<int> x(10);
    // for(int i = 0; i < 10; i++)
    //     x.insert(i, i+1);
    // std::cout << x << std::endl;
    // func(x);
    // std::cout << x << std::endl;
}

// Scale   elapsedTime     Time per reverse
// 10      1000    0.000476357
// 20      1000    0.000791031
// 30      1000    0.00110538
// 40      1000    0.0014133
// 50      1000    0.00231472
// 60      1000    0.00216559
// 70      1000    0.00237099
// 80      1000    0.00271424
// 90      1000    0.00298555
// 100     1000    0.00331219
// 200     1000    0.00645599
// 300     1000    0.00997944
// 400     1000    0.0126549
// 500     1000    0.0158506
// 600     1000    0.0190382
// 700     1000    0.0222252
// 800     1000    0.0254033
// 900     1000    0.0287439
// 1000    1000    0.0316286

// Scale   elapsedTime     Time per reverse
// 10      1000    0.000430018
// 20      1000    0.000681011
// 30      1000    0.00146001
// 40      1000    0.00153879
// 50      1000    0.00213667
// 60      1000    0.00193174
// 70      1000    0.00202426
// 80      1000    0.00229393
// 90      1000    0.0024908
// 100     1000    0.00290708
// 200     1000    0.00553189
// 300     1000    0.00825866
// 400     1000    0.0110022
// 500     1000    0.0137067
// 600     1000    0.0163351
// 700     1000    0.0188448
// 800     1000    0.0218293
// 900     1000    0.0245272
// 1000    1000    0.028609



// Scale   elapsedTime     Time per reverse
// 1000    1000    0.0417816
// 5000    1000    0.158053
// 10000   1000    0.320616

// Scale   elapsedTime     Time per reverse
// 1000    1000    0.0418778
// 5000    1000    0.168976
// 10000   1000    0.314268