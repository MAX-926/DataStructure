//7.1)
//对栈的ADT进行扩充，增加以下函数
//i.输入栈
//ii.将一个栈转变为一个适合输出的串
//iii.将一个栈分裂为两个栈。第一个栈包含从栈底开始的一半元素，第二个栈包含剩余元素。
//iv.将两个栈合并，把第二个栈的所有元素置于第一个栈的顶部，不改变第二个栈中所有元素的相对顺序

/*
The extensions are
input( ):
Input a stack from bottom to top;
toString( ):
Return the stack elements, as a string, from bottom to top;
split(a, b):
Split a stack into the stacks a and b. Stack a contains the bottom-half elements, and stack b contains the remaining elements.
combine(a, b):
Combine the stacks a and b into a single stack. The elements in the combined stack are the result of placing stack b on top of stack a.
*/

#include<iostream>
#include"../../Tool.h"
using namespace std;

template<class T>
class extendedStack;

template<class T>
class stack
{
    public:
        virtual ~stack(){}
        virtual bool empty()const = 0;
        virtual int size()const = 0;
        virtual T& top() = 0;
        virtual void pop() = 0;
        virtual void push(const T& theElement) = 0;
        //ADT新增部分
        //i.输入栈
        // virtual istream& operator>>(istream& in, stack<T>& theStack)const = 0;
        //ii.将一个栈转变为一个适合输出的串
        virtual string transform()const = 0;
        //iii.将一个栈分裂为两个栈。第一个栈包含从栈底开始的一半元素，第二个栈包含剩余元素。
        // virtual void split(stack<T>& theExtendedStack) = 0;
        virtual void split(extendedStack<T>& theExtendedStack) = 0;//使用不完全类型说明以定义未知类型的引用参数！！！
        //iv.将两个栈合并，把第二个栈的所有元素置于第一个栈的顶部，不改变第二个栈中所有元素的相对顺序
        virtual void add(extendedStack<T>& theExtendedStack) = 0;
};

template<class T>
class extendedStack:public stack<T>
{
    public:
        //consturctor, copy-constructor and destructor
        extendedStack(int initialCapacity = 10);
        extendedStack(const extendedStack<T>& theExtendedStack);
        ~extendedStack()
        {
            if(stack != nullptr)
                delete[] stack;
        }
        //ADT methods:
        bool empty()const{return stackTop == -1;}
        int size()const{return stackTop + 1;}
        T& top()
        {
            if(empty()) throw stackEmpty();
            return stack[stackTop];
        }
        void pop()
        {
            if(empty()) throw stackEmpty();
            stack[stackTop--].~T();
        }
        void push(const T& theElement)
        {
            int oldSize = size();
            if(oldSize == arrayLength)
            {
                T* newStack = new T[oldSize*2];
                copy(stack, stack+oldSize, newStack);
                delete[] stack;
                stack = newStack;
                arrayLength = oldSize*2;
            }
            stack[++stackTop] = theElement;
        }
        // istream& operator>>(istream& is, extendedStack<T>& theExtendedStack);
        // istream& transform()const;
        string transform()const;
        void split(extendedStack<T>&);
        void add(extendedStack<T>& theExtendedStack);
    private:
        T* stack;
        int arrayLength;
        int stackTop;
};

template<class T>
extendedStack<T>::extendedStack(int initialCapacity):stack<T>()
{
    if(initialCapacity < 1)
        throw illegalParameter("initialCapacity must be > 0");
    stack = new T[initialCapacity];
    arrayLength = initialCapacity;
    stackTop = -1;
}

template<class T>
extendedStack<T>::extendedStack(const extendedStack<T>& theExtendedStack)
{
    arrayLength = theExtendedStack.arrayLength;
    stackTop = theExtendedStack.stackTop;
    stack = new T[arrayLength];
    copy(theExtendedStack.stack, theExtendedStack.stack+theExtendedStack.size(), stack);
}

// template<class T>
// istream& operator>>(istream& is, extendedStack<T>& theExtendedStack)
// {
//     cout << "input stack elements:\n";
//     T newTerm;
//     while(is >> newTerm;)
//     {
//         theExtendedStack<T>.push(newTerm);
//     }
// }

template<class T>
string extendedStack<T>::transform()const
{
    string str;
    for(int i = 0; i <= stackTop; i++)
        //可以将整型数据转换为string能接受的类型
        str += to_string(stack[i]);
    return str;
}

template<class T>
void extendedStack<T>::split(extendedStack<T>& theExtendedStack)
{
    int theSize = size();
    if(theSize == 1)
    {
        cout << "not enough elements to split";
        return;
    }
    int theTop = (theSize-1)/2;
    //开始分裂
    while(!theExtendedStack.empty())
        theExtendedStack.pop();
    for(int i = theTop+1; i < theSize; i++)
        theExtendedStack.push(stack[i]);
    //为原始stack创建新的存储空间
    T* newStack = new T[theTop+1];
    copy(stack, stack+theTop+1, newStack);
    delete[] stack;
    stack = newStack;
    stackTop = theTop;
    arrayLength = theTop+1;
}

template<class T>
void extendedStack<T>::add(extendedStack<T>& theExtendedStack)
{
    if(theExtendedStack.empty())
        return;
    int theExtendedStackSize = theExtendedStack.size();
    for(int i = 0; i < theExtendedStackSize; i++)
        push(theExtendedStack.stack[i]);
    while(!theExtendedStack.empty())
        theExtendedStack.pop();
}

int main()
{
    //测试add和split
    // extendedStack<int> s;
    // for(int i = 0; i < 5; i++)
    //     s.push(i);
    // extendedStack<int> s1(s);
    // s1.pop();
    // //s:01234
    // //s1:0123
    // s.add(s1);
    // //s:012340123
    // //s1:
    // s.split(s1);
    // //s:01234
    // //s1:0123
    // cout << "s:\n";
    // for(int i = 0; i < 4; i++)
    // {
    //     cout << s.top() << endl;
    //     s.pop();
    // }
    // cout << "s1:\n";
    // for(int i = 0; i < 4; i++)
    // {
    //     cout << s1.top() << endl;
    //     s1.pop();
    // }

    //测试transform
    extendedStack<int> s;
    for(int i = 0; i < 5; i++)
        s.push(i);
    cout << s.transform();
}