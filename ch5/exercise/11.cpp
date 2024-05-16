#include"../case/5-3.h"
#include<iterator>
template<class T>
class arrayListWithPushBack:public arrayList<T>
{
    public:
        arrayListWithPushBack(int initialCapacity = 10):arrayList<T>(initialCapacity){}
        void push_back(const T theElement);
        void output(std::ostream& out) const;
        // std::ostream& operator<<(std::ostream&, const arrayListWithPushBack<T> &x);
    private:
        void inflate(int expanision = 2);
};

template<class T>
void arrayListWithPushBack<T>::output(std::ostream &out) const
{
    std::copy(this->element, (this->element)+(this->listSize), std::ostream_iterator<T>(std::cout, " "));
}

template<class T>
std::ostream& operator<<(std::ostream& out, const arrayListWithPushBack<T> &x)
{
    x.output(out); return out;
}

template<class T>
void arrayListWithPushBack<T>::inflate(int expanision)
{
    T* tmp = new T[expanision*(this->arrayLength)];
    std::copy((this->element), (this->element)+(this->listSize), tmp);
    delete [](this->element);
    (this->element) = tmp;
    (this->arrayLength) = expanision*(this->arrayLength);    
}

template<class T>
void arrayListWithPushBack<T>::push_back(const T theElement)
{
    if(this->listSize == this->arrayLength) inflate();
    (this->element)[(this->listSize)] = theElement;
    (this->listSize) += 1;
}

int main()
{
    arrayListWithPushBack<int> x(2);
    x.push_back(1);
    x.push_back(2);
    std::cout << x.capacity() << std::endl;
    x.push_back(3);
    x.push_back(4);
    x.push_back(5);
    std::cout << x.capacity();
    std::cout << std::endl << x.size();
}