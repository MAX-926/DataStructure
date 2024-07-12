//开发一个新类arrayStack，以消除继承带来的额外的不必要的开销

#include"8-1.h"
#include"E:\DataStructure\Tool.h"

template<class T>
class arrayStack:public stack<T>
{
    public:
        arrayStack(int initialCapacity = 10);
        arrayStack(const arrayStack<T>& theArrayStack);
        ~arrayStack(){delete[] stack;}
        //ADT methods:
        bool empty()const{return stackTop == -1;}
        int size()const{return stackTop+1;}
        T& top()
        {
            if(stackTop == -1)
                throw stackEmpty();
            return stack[stackTop];
        }
        void push(const T& theElement)
        {
            int oldSize = size();
            if(size() == arrayLength)
            {
                T* newArray = new T[oldSize*2];
                copy(stack, stack+oldSize, newArray);
                delete[] stack;
                stack = newArray;
                arrayLength = oldSize*2;
            }
            stack[++stackTop] = theElement;
        }
        void pop();// pop function that could decease its size when its nums of elements is less than 1 / 4 of its capacity
        //Old pop:
        // {
        //     if(stackTop == -1)
        //         throw stackEmpty();
        //     stack[stackTop--].~T();
        // }
        void showCapacity(){cout << "Capacity:" << arrayLength << endl;}
    private:
        T* stack;
        int stackTop;
        int arrayLength;
};

template<class T>
arrayStack<T>::arrayStack(int initialCapacity):stack<T>()
{
    if(initialCapacity < 1)
        throw illegalParameter("listSize must be > 0");
    stack = new T[initialCapacity];
    arrayLength = initialCapacity;
    stackTop = -1;
}

template<class T>
arrayStack<T>::arrayStack(const arrayStack<T>& theArrayStack)
{
    arrayLength = theArrayStack.arrayLength;
    stackTop = theArrayStack.stackTop;
    stack = new T[arrayLength];
    copy(theArrayStack.stack, theArrayStack.stack+size(), stack);
}

template<class T>
void arrayStack<T>::pop()
{
    if(empty())
        throw stackEmpty();
    stack[stackTop--].~T();
    int theSize = stackTop + 1;
    if(theSize < arrayLength/4)
    {//将容量减少为原来的一半

        T* newStack = new Tqws[arrayLength/2];
        copy(stack, stack+theSize, newStack);
        delete[] stack;
        stack = newStack;
        arrayLength /= 2;
    }
}
//练习8已证明，若以倍数因子放大数组容量，则n次push操作过后，总的操作用时仍为O(n)
//假设n-1次pop，则有m=log2n - 1次缩容，缩容共计耗时O(n/2 - 1),即O(n)
// 主要缩容开销(移动、拷贝数据):2n + n + n/2 + ... + 2
int main()
{
    arrayStack<int> s;
    for(int i = 0; i < 5; i++)
        s.push(i);
    s.showCapacity();
    for(int i = 0; i < 4; i++)
        s.pop();
    s.showCapacity();
}
