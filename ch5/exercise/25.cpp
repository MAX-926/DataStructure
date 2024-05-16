#include"../case/5-3.h"
#include<time.h>

template<class T>
class arrayListWithHalf:public arrayList<T>
{
    public:
        arrayListWithHalf(int initialCapacity = 10):arrayList<T>(initialCapacity){}
        void half();
};

template<class T>
void arrayListWithHalf<T>::half()
{
    // if(this->listSize == 0) {return;}
    // int newLength = (this->listSize) - (this->listSize)/2;
    // T* tmp = new T[newLength];
    // for(int i = 0; i < newLength && 2*i < (this->listSize); i++)
    //     tmp[i] = (this->element)[2*i];
    // delete [](this->element);
    // this->element = tmp;
    // this->listSize = newLength;
    // this->arrayLength = newLength;

    //原地處理
    if(this->listSize == 0) return;
    int newLength = (this->listSize) - (this->listSize)/2;
    for(int i = 2; i < this->listSize; i += 2)
        (this->element)[i/2] = (this->element)[i];
    for(int i = newLength; i < (this->listSize); i++)
        (this->element)[i].~T();
    this->listSize = newLength;
    this->arrayLength = newLength;//Q：對象T被析構，容量理應減小？
}

int main()
{
    //測試half
    arrayListWithHalf<int> x(4);
    // for(int i = 0; i < 5; i++)
    //     x.insert(i, i+1);
    // x.insert(0, 2);
    // x.insert(1, 13);
    // x.insert(2, 4);
    // x.insert(3, 5);
    std::cout << x << std::endl;
        x.half();
    std::cout << x << std::endl;
}

    //測試half的性能
    // double clocksPerMillis = CLOCKS_PER_SEC / 1000;
    // int step = 10;
    // std::cout << "Scale" << '\t' << "elapsedTime" << '\t' << "Time per half()" << std::endl;
    // for(int n = 10; n <= 1000; n += step)
    // {
    //     double numbersOfRepetions = 0;
    //     clock_t startTime = clock();
    //     do
    //     {
    //         numbersOfRepetions++;
    //         arrayListWithHalf<int> x(n);
    //         for(int i = 0; i < n; i++)
    //             x.insert(i, i+1);
    //         x.half();
    //     }while(clock() - startTime < 1000);
    //     double elapsedTime = clock() - startTime;
    //     std::cout << n << '\t' << elapsedTime << '\t' << elapsedTime/clocksPerMillis/numbersOfRepetions << std::endl;
    //     if(n == 100) {step = 100;}
    // }

// Scale   elapsedTime     Time per half()
// 10      1000    0.000689156
// 20      1000    0.000878119
// 30      1000    0.00108054
// 40      1000    0.00133875
// 50      1000    0.00160489
// 60      1000    0.00206453
// 70      1000    0.00229652
// 80      1000    0.00249667
// 90      1000    0.00287974
// 100     1000    0.00309141
// 200     1000    0.00587599
// 300     1000    0.00869134
// 400     1000    0.0140788
// 500     1000    0.0151828
// 600     1000    0.0172354
// 700     1000    0.0212143
// 800     1000    0.0230675
// 900     1000    0.0258692
// 1000    1000    0.0286566

    //測試half
    // arrayListWithHalf<int> x(1);
    // for(int i = 0; i < 5; i++)
    //     x.insert(i, i+1);
    // x.insert(0, 2);
    // x.insert(1, 13);
    // x.insert(2, 4);
    // x.insert(3, 5);
    // std::cout << x << std::endl;
        // x.half();
    // std::cout << x << std::endl;