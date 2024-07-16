#include"../../ch6/case/6-2.h"
#include"8-1.h"
#include"../../Tool.h"

template<class T>
class derivedLinkedStack:private chain<T>, public stack<T>
{
    public:
        derivedLinkedStack(int initialCapacity = 10):chain<T>(initialCapacity){}//O(1)
        bool empty()const{return chain<T>::empty();}//O(1)
        int size()const{return chain<T>::size();}//O(1)
        T& top()//O(1)
        {
            if(empty())//O(1)
                throw stackEmpty();
            return chain<T>::get(0);//O(1)
        }
        void push(const T& theElement)//O(1)
        {
            chain<T>::insert(0, theElement);//O(1)
        }
        void pop()//O(1)
        {
            if(empty())//O(1)
                throw stackEmpty();
            chain<T>::erase(0);//O(1)
        }
};

// int main()
// {
//     derivedLinkedStack<int> dls;
//     for(int i = 0; i < 5; i++)
//         dls.push(i);
//     for(int i = 0; i < 5; i++)
//     {
//         cout << dls.top();
//         dls.pop();
//     }
// }