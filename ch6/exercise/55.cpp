#include"../case/bidirectionalChainNode.h"
#include"../case/6-11.h"

template<class T>
class doubleCircularListWithHeader:public extendedLinearList<T>
{
    public:
        doubleCircularListWithHeader();
        doubleCircularListWithHeader(const doubleCirculatListWithHeader<T> &theDCLH);
        ~doubleCircularListWithHeader();
        //ADT methods:
        bool empty()const{return listSize == 0;}
        int size(){return listSize;}
        T& get(int theIndex);
        int indexOf(const T& theElement)const;
        void insert(int theIndex, const T& theElement);
        void erase(int theIndex);
        void push_back(const T& theElement);
        void clear();
    protected:
        void checkIndex(int theIndex)const;
        bdChainNode<T>* header;
        // bdChainNode<T>* lastNode;
        int listSize;
};