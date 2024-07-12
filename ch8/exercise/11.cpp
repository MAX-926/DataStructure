//TwoStacks
//用一个数组描述两个栈。一个栈底在0的位置，另一个在arrayLength-1的位置。两个栈都向数组中间增长。
//该类的方法必须在每一个栈中实施ADT栈的所有操作，且每一个方法的复杂度应该为O(1)。其中不包括改变数组大小所需要的时间

#include"../case/8-1.h"
#include"../../Tool.h"
#include<sstream>
using namespace std;

template<class T>
class twoStacks:public stack<T>
{
    public:
    //constructor, copy-constructor and destructor
        twoStacks(int initialCapacity = 10);
        twoStacks(const twoStacks<T>&);
        ~twoStacks(){if(theTwoStacks != nullptr) delete[] theTwoStacks;}
    //ADT methods:
    //for "0" stack:
        bool empty()const{return stackTopL == -1;}
        int size()const{return stackTopL+1;}
        T& top();
        void push(const T&);
        void pop();
    //for "arrayLength-1" stack
        bool emptyR()const{return stackTopR == arrayLength;}
        int sizeR()const{return arrayLength-stackTopR;}
        T& topR();
        void pushR(const T&);
        void popR();
    //查看栈内部细节的工具
        // void showArrayLength(){cout << arrayLength;}
        // void showStackElements();
    private:
        T* theTwoStacks;//两个栈所使用的数组空间
        int arrayLength;//数组twoStacks的长度
        int stackTopL;//左栈的栈顶索引
        int stackTopR;//右栈的栈顶索引
};

// template<class T>
// void twoStacks<T>::showStackElements()
// {
//     for(int i = 0; i < arrayLength; i++)
//         cout << theTwoStacks[i] << endl;
// }

template<class T>
twoStacks<T>::twoStacks(int initialCapacity)//O(1) or O(initialCapacity),主要开销在创建数组上
{
    if(initialCapacity < 1)//O(1)
    {
        ostringstream s;
        s << "initialCapacity:" << initialCapacity << " must be > 0";
        throw illegalParameter(s.str());
    }
    theTwoStacks = new T[initialCapacity];//O(1) or O(initialCapacity)
    arrayLength = initialCapacity;
    stackTopL = -1;
    stackTopR = arrayLength;
}

template<class T>
twoStacks<T>::twoStacks(const twoStacks<T>& ts)//O(arrayLength)
{
    arrayLength = ts.arrayLength;
    theTwoStacks = new T[arrayLength];//O(1) or O(arrayLength)
    stackTopL = ts.stackTopL;
    stackTopR = ts.stackTopR;
    copy(ts.theTwoStacks, ts.theTwoStacks+arrayLength, theTwoStacks);//O(arrayLength)
}

template<class T>
T& twoStacks<T>::top()//O(1)
{
    if(stackTopL == -1) throw stackEmpty();//O(1)
    return theTwoStacks[stackTopL];//O(1)
}

template<class T>
void twoStacks<T>::push(const T& theElement)//O(nums of elements) or O(arrayLength*2)
{
    if(stackTopL+1 == stackTopR)//O(nums of elements) or O(arrayLength*2)
    {//扩容
        T* newStack = new T[arrayLength*2];//O(1) or O(arrayLength*2)
        copy(theTwoStacks, theTwoStacks+stackTopL+1, newStack);//O(elements nums of left stack)
        copy(theTwoStacks+stackTopR, theTwoStacks+arrayLength, newStack+((arrayLength*2-(arrayLength-stackTopR))));//O(elements nums of right stack)
        stackTopR = arrayLength*2-(arrayLength-stackTopR);
        arrayLength *= 2;
        delete[] theTwoStacks;//O(1) or O(arrayLength)
        theTwoStacks = newStack;
    }
    theTwoStacks[++stackTopL] = theElement;//O(1)
}

template<class T>
void twoStacks<T>::pop()//O(1)
{
    if(stackTopL == -1)//O(1)
        throw stackEmpty();
    theTwoStacks[stackTopL--].~T();//O(1)
}

template<class T>
T& twoStacks<T>::topR()//O(1)
{
    if(stackTopR == arrayLength)//O(1)
        throw stackEmpty();
    return theTwoStacks[stackTopR];//O(1)
}

//1 2 3 4 0 0 4 3 2 1
template<class T>
void twoStacks<T>::pushR(const T& theElement)//O(nums of two stacks elements) or O(arrayLength*2)
{
    if(stackTopL+1 == stackTopR)//O(nums of two stacks elements) or O(arrayLength*2)
    {//扩容
        T* newStack = new T[arrayLength*2];//O(1) or O(arrayLength*2)
        copy(theTwoStacks, theTwoStacks+stackTopL+1, newStack);//O(nums of left stack elements)
        copy(theTwoStacks+stackTopR, theTwoStacks+arrayLength, newStack+((arrayLength*2-(arrayLength-stackTopR))));//O(nums of right stack elements)
        stackTopR = arrayLength*2-(arrayLength-stackTopR);
        arrayLength *= 2;
        delete[] theTwoStacks;//O(1) or O(arrayLength)
        theTwoStacks = newStack;
    }
    theTwoStacks[--stackTopR] = theElement;//O(1)
}

template<class T>
void twoStacks<T>::popR()//O(1)
{
    if(stackTopR == arrayLength)/O(1)
        throw stackEmpty();
    theTwoStacks[stackTopR++].~T();//O(1)
}

int main()
{
    twoStacks<int> ss(19);
    for(int i = 0; i < 10; i++)
        ss.push(i);
    for(int i = 0; i < 10; i++)
        ss.pushR(i);
    twoStacks<int> ssCpy(ss);
    for(int i = 0; i < 10; i++)
    {
        cout << ss.top();
        ss.pop();
    }
    cout << endl;
    for(int i = 0; i <= 10; i++)
    {
        cout << ss.topR();
        ss.popR();
    }
    cout << endl;
    // for(int i = 0; i < 10; i++)
    // {
    //     cout << ssCpy.top();
    //     ssCpy.pop();
    // }
    // cout << endl;
    // for(int i = 0; i < 10; i++)
    // {
    //     cout << ssCpy.topR();
    //     ssCpy.popR();
    // }

    // ss.showStackElements();
    // cout << "ss.Lstack size = " << ss.size() << endl;
    // cout << "ss.Rstack size = " << ss.sizeR() << endl;
    // ss.showArrayLength();
}