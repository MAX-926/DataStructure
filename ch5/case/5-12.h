#ifndef CH5_5_12_H
#define CH5_5_12_H
//利用vector實現的基於數組的綫性表
#include<vector>
#include"5-1.h"
using namespace std;
template<class T>
class vectorList:public linearList<T>
{
    public:
        vectorList(int initialCapacity = 10);
        vectorList(const vectorList<T> &theList);
        ~vectorList(){delete element;}
    //ADT methods
        bool empty()const{ return element->empty();}
        int size()const{return element->size();}
        T& get(int theIndex)const{return (*element)[theIndex];}
        int indexOf(const T &theElement)const;
        void insert(int theIndex, const T &theElement);
        void erase(int theIndex);
        void output(std::ostream& out)const;
        // new method
        int capacity()const{return (int)element->capacity();}
        typedef typename std::vector<T>::iterator iterator;
        iterator begin()const{return element->begin();}
        iterator end()const{return element->end();}
    protected:
        void checkIndex(int theIndex)const;
        std::vector<T>* element;
};

template<class T>
std::ostream& operator<<(std::ostream& out, const vectorList<T> &theList)
{
    theList.output(out);
    return out;
}

#endif //ch5_5_12_h