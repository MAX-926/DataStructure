#include"../case/5-3.h"
#include<time.h>
#include<iterator>
template<class T>
class arrayListWithSetSize:public arrayList<T>
{
    public:
        //constructor and destructor
        arrayListWithSetSize(int initialCapacity = 10):arrayList<T>(initialCapacity){}
        void setSize(int theSize);
        void output(std::ostream&) const;
};

template<class T>
void arrayListWithSetSize<T>::output(std::ostream& out) const
{
    std::copy((this->element), (this->element) + (this->listSize), std::ostream_iterator<T>(std::cout, " "));
}

template<class T>
std::ostream& operator<<(std::ostream& out, const arrayListWithSetSize<T> &x)
{
    x.output(out);  return out;
}

template<class T>
void arrayListWithSetSize<T>::setSize(int theSize)
{
    if(theSize == this->listSize) return;
    if(theSize < 0)
    {
        std::ostringstream s;
        s << "Size = " << theSize << " Size must be >= 0";
        throw IllegalParameter(s.str());
    }
    else if(theSize == 0) 
    {
        delete [](this->element);
        this->element = new T[1];
        this->listSize = 0;
        this->arrayLength = 1;
    }
    else
    {
        T* tmp = new T[theSize];//O(theSize)
        int copyElementNum = theSize >= (this->listSize) ? (this->listSize) : theSize;
        std::copy(this->element, (this->element)+copyElementNum, tmp);//O(copyElementNum)
        delete [](this->element);
        this->element = tmp;
        this->listSize = copyElementNum;
        this->arrayLength = theSize;
    }

}

 template<class T>
 class simple:public arrayList<T>
 {
    public:
        simple():i(0), arrayList<T>(10){}
        bool operator!=(const simple &x){return i != x.i;}
    private:
        T i;
 };

int main()
{
    arrayListWithSetSize<simple<int>> a;
    a.setSize(0);
    double n = 1000, step = 100, numberOfRepetions = 0;
    clock_t clocksPerMillis = CLOCKS_PER_SEC / 1000;
    //打印待输出的信息
    std::cout << "Scale" << '\t' << "elapsedTime" << '\t' << "Time per set" << std::endl;
    for(double theSize = 0; theSize <= n; theSize += step)
    {
        numberOfRepetions = 0;
        clock_t startTime = clock();
        do
        {
            numberOfRepetions++;
            a.setSize(theSize);
        }while((clock() - startTime) < 1000);
        double elapsedTime = (double)((clock()-startTime)/clocksPerMillis);
        std::cout << theSize << '\t' << elapsedTime*clocksPerMillis << '\t' << elapsedTime/numberOfRepetions << std::endl;
        // if(theSize == 100){ step = 100;}
    }
}
//T为用户自建类型时，复杂度为 O(n)，普通类型为O(1)
//Scale   elapsedTime     Time per set
// 0       1000    1.0193e-05
// 100     1000    0.0120863
// 200     1000    0.0221882
// 300     1000    0.0326307
// 400     1000    0.0432227
// 500     1000    0.0579005
// 600     1000    0.0725531
// 700     1000    0.0850051
// 800     1000    0.0987459
// 900     1000    0.100361
// 1000    1000    0.111359
