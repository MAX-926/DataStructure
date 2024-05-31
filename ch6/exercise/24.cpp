#include"../case/6-2.h"

template<class T>
class moveLeftAndRightOnChain:public chain<T>
{
    public:
        moveLeftAndRightOnChain(int initialCapacity = 10):chain<T>(initialCapacity, p(this->firstNode), l(NULL)){}
        void moveRight();
        void moveLeft();
        T& currentElement()const;
        T& previousElement()const;
    protected:
        chainNode<T>* p;
        chainNode<T>* l;
};

template<class T>
void moveLeftAndRightOnChain<T>::moveRight()
{
    
}

template<class T>
void moveLeftAndRightOnChain<T>::moveLeft()
{

}

template<class T>
T& moveLeftAndRightOnChain<T>::currentElement()const
{}

template<class T>
T& moveLeftAndRightOnChain<T>::previousElement()const
{}