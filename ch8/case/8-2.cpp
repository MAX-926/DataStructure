//数组描述
//一个从arrayList派生出来的数组栈类
//这种做法会带来性能损失：因为linearList是通用线性表，而很多操作，如通用的insert是stack所不允许的（不需要的），所以会有响应的无效操作的代价（如下标检查，copy-backward等等）
//一种解决方案是开发一个新的类，使其操作完全为stack打造
#include"8-1.h"
#include"../../ch5/case/5-3.h"
#include"../../Tool.h"

template<class T>
class derivedArrayStack:private arrayList<T>, public stack<T>
{
    public:
        //constructor, copy-constructor and destructor
        derivedArrayStack(int initialCapacity = 10):arrayList<T>(initialCapacity){}//O(initialCapacity) or O(1)
        //ADT methods;
        bool empty()const{return arrayList<T>::empty();}//O(1)
        int size()const{return arrayList<T>::size();}//O(1)
        T& top()//O(1)
        {
            if(arrayList<T>::empty())//O(1)
                throw stackEmpty();
            else
                return arrayList<T>::get(arrayList<T>::size()-1);//O(1)
            //也可以不做异常抛出，因为arrayList<T>针对空栈做索引也会抛出异常，但类型为illegalParameter，会使用户感到困惑，这里可以通过try-catch结构来将捕获的异常转换并抛出        
            // try{return arrayList<T>::get(arrayList<T>::size()-1);}
            // catch(IllegalParameter){throw stackEmpty();}
            // from class derivedArrayStackWithCatch
        }
        void push(const T& theElement)//O(1) or O(oldListSize)
            {arrayList<T>::insert(arrayList<T>::size(), theElement);}
        void pop()//O(1)
        {
            if(arrayList<T>::empty())//O(1)
                throw stackEmpty();
            arrayList<T>::erase(arrayList<T>::size()-1);//O(1)
        }
        // void output(ostream& out)const;
};

// template<class T>
// ostream& operator<<(ostream& out, const derivedArrayStack<T>& das)
// {
//     das.output(out);
//     return out;
// }

// template<class T>
// void derivedArrayStack<T>::output(ostream& out)const
// {
//     for(int i = arrayList<T>::size(); i >= 0; i--)
//         out << arrayList<T>::get(i) << endl;
// }

int main()
{
    derivedArrayStack<int> das(5);
    for(int i = 0; i <  5; i++)
        das.push(i);
    das.pop();
    das.pop();
    das.pop();
    das.pop();
    das.pop();
    cout << das.top();
}