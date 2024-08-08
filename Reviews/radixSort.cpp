#include"ch5/case/5-1.h"
#include<iostream>
#include<sstream>
#include"Tool.h"
#include<math.h>
using namespace std;

template<class T>
struct myChainNode
{
    //constructor & copy-constructor
    myChainNode(const T &theElement = 0, myChainNode<T>* theNext = nullptr):element(theElement), next(theNext){}
    //data:
    T element;
    //pointer:
    myChainNode<T>* next;
};

template<class T>
class myChain:public linearList<T>
{
    public:
        myChain();
        myChain(const myChain<T> &theChain);
        ~myChain();
        //ADT mrthods:
        bool empty()const{return listSize == 0;}
        int size()const{return listSize;}
        T& get(int theIndex)const;
        int indexOf(const T& theElement)const;
        void insert(int theIndex, const T &theElement);
        void erase(int theIndex);
        void output(ostream& out)const;
        //radixSort: r为基数， d为分解的数字之个数
        void radixSort(int r, int d);
    protected:
        void checkIndex(int theIndex)const;
        myChainNode<T>* firstNode;
        int listSize;
};

template<class T>
void myChain<T>::checkIndex(int theIndex)const
{
    if(theIndex < 0 || theIndex >= listSize)
    {
        ostringstream s;
        s << "theIndex = " << theIndex << " listSize = " << listSize;
        throw illegalParameter(s.str());
    }
}

template<class T>
myChain<T>::myChain()
{
    firstNode = nullptr;
    listSize = 0;
}

template<class T>
myChain<T>::myChain(const myChain<T> &theChain)
{
    
}

template<class T>
myChain<T>::~myChain()
{
    while(firstNode)
    {
        myChainNode<T>* nextNode = firstNode->next;
        // std::cout << "delete Node: " << firstNode->element << std::endl;
        delete firstNode;
        firstNode = nextNode;
    }
}

template<class T>
T& myChain<T>::get(int theIndex)const
{
    checkIndex(theIndex);
    myChainNode<T>* currentNode = firstNode;
    for(int i = 0; i < theIndex; i++)
        currentNode = currentNode->next;
    return currentNode->element;
}

template<class T>
int myChain<T>::indexOf(const T& theElement)const
{
    myChainNode<T>* currentNode = firstNode;
    int index = 0;
    for(; currentNode != nullptr && currentNode->element != theElement ; index++, currentNode = currentNode->next);
    if(currentNode != nullptr) return index;
    else return -1;
}

template<class T>
void myChain<T>::insert(int theIndex, const T &theElement)
{
    if(theIndex < 0 || theIndex > listSize)
    {
        ostringstream s;
        s << "theIndex = " << theIndex << " listSize = " << listSize;
        throw illegalParameter(s.str());
    }
    if(listSize == 0)
    {
        firstNode = new myChainNode<T>(theElement, nullptr);
        listSize++;
        return;
    }
    else
    {
        if(theIndex == 0)
        {
            firstNode = new myChainNode<T>(theElement, firstNode);
            listSize++;
            return;
        }
        else
        {
            myChainNode<T>* currentNode = firstNode;
            for(int i = 0; i < theIndex-1; i++)
                currentNode = currentNode->next;
            myChainNode<T>* nextNode = currentNode->next;
            currentNode->next = new myChainNode<T>(theElement, nextNode);
            listSize++;
            return;
        }
    }
}

template<class T>
void myChain<T>::erase(int theIndex)
{
    checkIndex(theIndex);
    if(theIndex == 0)
    {
        myChainNode<T>* deleteNode = firstNode;
        firstNode = firstNode->next;
        delete deleteNode;
        listSize--;
        return;
    }
    else
    {
        myChainNode<T>* currentNode = firstNode;
        for(int i = 0; i < theIndex-1; i++)
            currentNode = currentNode->next;
        myChainNode<T>* deleteNode = currentNode->next;
        currentNode->next = deleteNode->next;
        delete deleteNode;
        listSize--;
        return;
    }
}

template<class T>
void myChain<T>::output(ostream& out)const
{
    if(firstNode == nullptr)
    {
        out << "";
        return;
    }
    myChainNode<T>* currentNode = firstNode;
    while(currentNode != nullptr)
    {
        out << currentNode->element << ' ';
        currentNode = currentNode->next;
    }
}

template<class T>
ostream& operator<<(ostream& out, const myChain<T> &theChain)
{
    theChain.output(out);
    return out;
}

template<class T>
void myChain<T>::radixSort(int r, int d)
{
    if(d < 1 || r < 1)
    {
        ostringstream s;
        s << "wrong input: " << "r: " << r << " " << "d: " << d  << " both must be > 1";
        throw illegalParameter(s.str());
    }
    //产生基数个桶
    myChainNode<T> **bottom, **top;
    bottom = new myChainNode<T>*[r];
    top = new myChainNode<T>*[r];
    int exp = 1;
    //进行d次桶排序
    for(int i = 0; i < d; i++)
    {

        //根据数字进行桶排序
        for(int i = 0; i < r; i++)
            bottom[i] = top[i] = nullptr;
        for(; firstNode != nullptr; firstNode = firstNode->next)
        {
            int theBin = (firstNode->element) % (int)pow(r, exp) / (int)pow(r, exp-1);
            if(bottom[theBin] == nullptr)
                bottom[theBin] = top[theBin] = firstNode;
            else
            {
                top[theBin]->next = firstNode;
                top[theBin] = firstNode;
            }
        }
        //链接桶
        myChainNode<T>* y = nullptr;
        for(int i = 0; i < r; i++)
        {
            if(bottom[i] != nullptr)
            {
                if(y == nullptr)
                    firstNode = bottom[i];
                else
                    y->next = bottom[i];
            }
            y = top[i];
        }

        if(y != nullptr)
            y->next = nullptr;
        
        exp++;
    }
    delete []bottom;
    delete []top;
}

int main()
{
    myChain<int> a;
    for(int i = 0; i < 10; i++)
    {
        a.insert(i, 10-i);
    }
    cout << a << endl;
    a.erase(0);
    cout << a << endl;
    try
    {
        a.radixSort(20, 2);
    }catch(illegalParameter ip)
    {ip.showMsg();}
    cout << a << endl;
}