//使用栈实现表达式求值
//实现数组栈
#include"../case/8-1.h"
#include"../../Tool.h"

template<class T>
class arrayStack:public stack<T>
{
    public:
        arrayStack(int initialCapacity = 10)
        {
            arrayLength = initialCapacity;
            stackSize = 0;
            stack = new T[arrayLength];
            TOP = -1;
        }
        virtual ~arrayStack() { delete[] stack;}
        //ADT Methods:
        bool empty()const { return stackSize == 0;}
        int size()const { return stackSize;}
        T& top() {if(TOP == -1) throw stackEmpty(); return stack[TOP]; }
        void push(const T& theElement)
        {
            if(stackSize == arrayLength)
                inflate();
            stack[++TOP] = theElement;
            stackSize++;
        }
        void pop()
        {
            if(TOP == -1) throw stackEmpty();
            stack[TOP--].~T();
            stackSize--;
        }
    protected:
        void inflate();//完成栈的扩容
        T* stack;
        int stackSize;
        int TOP;
        int arrayLength;
};

template<class T>
void arrayStack<T>::inflate()
{
    T* newStack = new T[arrayLength*2];
    memcpy(newStack, stack, stackSize);
    arrayLength *= 2;
    delete[] stack;
    stack = newStack;
}

// int main(void)
// {
//    arrayStack<int> s;

//    // add a few elements
//    s.push(1);
//    s.push(2);
//    s.push(3);
//    s.push(4);

//    cout << "Stack should be 1234, bottom to top" << endl;

//    // test empty and size
//    if (s.empty())
//       cout << "The stack is empty" << endl;
//    else
//       cout << "The stack is not empty" << endl;

//    cout << "The stack size is " << s.size() << endl;

//    while (!s.empty())
//    {
//       cout << "Stack top is " << s.top() << endl;
//       s.pop();
//       cout << "Popped top element" << endl;
//    }

//    try {s.pop();}
//    catch (stackEmpty message)
//    {
//       cout << "Last pop failed " << endl;
//       message.outputMessage();
//    }

//    return 0;
// }


//实现表达式求值的算法

//表达式形如：（1 + 2）* 3 - 4 / 5
//包含+-*/与（），处理整数

template<class T>
class calculator
{
    public:
        calculator(){}
        ~calculator(){}
        void cal(const char*);//输入表达式计算并输出结果
    private:
        arrayStack<char> symbol;
        arrayStack<char> parenthese;
        arrayStack<T> number;
};

