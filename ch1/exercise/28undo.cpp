//编写C++代码实现四个参数的模版函数accumulate。测试代码。
#include<iostream>
using namespace std;

template<class T>
class Operator
{
    public:
        Operator(){}
        // virtual ~Operator() = 0;
        // virtual T operator()(T, T) = 0;
        virtual T getValue() = 0;
    private:
};

template<class T>
class Add:public Operator<T>
{
    public:
        Add():value(0){}
        //let compiler complement desconstructor 
        // T operator()(T t1, T t2){return t1+t2;}
        int getValue(){return value;} 
    private:
         int value;
};

template<class T>
class Mul:public Operator<T>
{
    public:
        Mul():value(1){}
        //let compiler complement desconstructor 
        // T operator()(T t1, T t2){return t1*t2;}
        int getValue(){return value;} 
    private:
         int value;
};

template<class T>
T accumulate(T an[], T* tp, T initValue, Operator<T>* op)
{
    //+ - * /
    if(op->getValue() == 0)
        for(int i = 0; i < tp-an; i++)
            initValue += an[i];
    return initValue;
    if(op->getValue() == 1)
        for(int i = 0; i < tp-an; i++)
            initValue *= an[i];        
}

int main()
{
    int a[] = {1, 2, 3, 4, 5};
    Add<int> ad;
    cout << accumulate<int>(a, a+5, 0, &ad);
}