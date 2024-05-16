
#include"../case/5-3.h"
template<class T>
class arrayListWithSet:public arrayList<T>
{
    public:
        arrayListWithSet(int initialCapacity = 10):arrayList<T>(initialCapacity){}
        T set(int theIndex, const T &theElement);
};

template<class T>
T arrayListWithSet<T>::set(int theIndex, const T& theElement)
{
    this->checkIndex(theIndex);
    T tmp = (this->element)[theIndex];
    (this->element)[theIndex] = theElement;
    return tmp;
}

int main()
{
    arrayListWithSet<int> x;
    for(int i = 0; i < 10; i++)
        x.insert(i, i+1);
    std::cout << x << std::endl;
    int reNum = x.set(0, 26);
    std::cout << x << std::endl << "reNum = " << reNum << std::endl;
    try
    {
        x.set(-1, -1);
    }catch(IllegalParameter ip){ip.outputMessage();}
}