#include"../case/5-12.h"
#include<math.h>

template<class T>
class vectorListWithHalf:public vectorList<T>
{
    public:
        vectorListWithHalf(int initialCapacity = 10):vectorList<T>(initialCapacity){}
        vectorListWithHalf(const vectorListWithHalf<T> &theList):vectorList<T>(theList){}
        ~vectorListWithHalf(){delete this->element;}
        //ADT methods
        void half();
};

template<class T>
void vectorListWithHalf<T>::half()
{
    int listSize = this->size();
    // //要執行listSize/2次刪除
    //     for(int i = 0; i < listSize/2; i++)
    //         this->erase(i+1);
    int i;
    for(i = 1; 2*i < listSize; i++)
        (*(this->element))[i] =  (*(this->element))[2*i];
    for(; i < listSize; i++)
        (*(this->element)).pop_back();
}

int main()
{
    vectorListWithHalf<int> x(10);
    for(int i = 0; i < 20; i++)
        x.insert(i, i+1);
    std::cout << x << std::endl;
    x.half();
    std::cout << x.size() << std::endl;
}