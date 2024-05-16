#include"../case/5-3.h"

template<class T>
class arrayListWithOperatorIndex:public arrayList<T>
{
    public:
        arrayListWithOperatorIndex():arrayList<T>(10){}
        T& operator[](int theIndex) const;
};

template<class T>
T& arrayListWithOperatorIndex<T>::operator[](int theIndex)const
{
   arrayList<T>:: checkIndex(theIndex);
    return (this->element)[theIndex];
}

int main()
{
    arrayListWithOperatorIndex<int> x;
    x.insert(0, 26);
    // int y = x[0];
    // std::cout << y << std::endl;
    // x[0] = 52;
    try
    {
    std::cout << x[-1.8];
    }catch(IllegalParameter ip){ip.outputMessage();}
}