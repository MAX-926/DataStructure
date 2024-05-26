#include"../case/6-2.h"

template<class T>
class chainListWithLeftShift:public chain<T>
{
    public:
        chainListWithLeftShift(int initialCapacity = 10):chain<T>(initialCapacity){}
        void leftShift(int numberOfSteps);
};

template<class T>
void chainListWithLeftShift<T>::leftShift(int numbersOfSteps)
{
    if(this->listSize == 0) return;//O(1)
    if(numbersOfSteps < 0)//O(1)
    {
        ostringstream s;
        s << "numberOfSteps = " << numbersOfSteps << " Must be > 0";
        throw IllegalParameter(s.str());
    }
    int deleteTimes = min(numbersOfSteps, this->listSize);
    for(int i = 0; i < deleteTimes; i++)//O(deleteTimes)
    {
        chainNode<T>* nextNode = this->firstNode->next;
        delete this->firstNode;
        this->firstNode = nextNode;
        --this->listSize;
    }
    return;
}

int main()
{
    chainListWithLeftShift<int> x;
    for(int i = 0; i < 5; i++)
        x.insert(i, i);
    cout << x << endl;
    x.leftShift(2);
    cout << x;
}

