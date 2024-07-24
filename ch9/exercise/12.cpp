#include"../../ch6/case/extendedChain.cpp"
#include"../case/9-1.h"

template<class T>
class linkedQueueFromExtendedChain:private extendedChain<T>, public queue<T>
{
    public:
        linkedQueueFromExtendedChain(int initialCapacity = 10):extendedChain<T>(initialCapacity), queue<T>(){}
        linkedQueueFromExtendedChain(const linkedQueueFromExtendedChain<T>& lqfec):extendedChain<T>(lqfec){}
        virtual ~linkedQueueFromExtendedChain(){}
        bool empty()const{return extendedChain<T>::empty();}
        int size()const{return extendedChain<T>::size();}
        T& front(){return extendedChain<T>::get(0);}
        T& back(){return extendedChain<T>::get(extendedChain<T>::size() - 1);}
        void push(const T& theElement){extendedChain<T>::push_back(theElement);}
        void pop(){extendedChain<T>::erase(0);}
};

// int main()
// {
//     linkedQueueFromExtendedChain<int> lqfec;
//     for(int i = 0; i < 20; i++)
//         lqfec.push(i);
//     linkedQueueFromExtendedChain<int> cpy(lqfec);
//     // cout << "front = " << lqfec.front() << endl << "back = " << lqfec.back() << endl;
//     for(int i = 0; i < 20; i++)
//     {
//         cout << cpy.front() << " ";
//         cpy.pop();
//     }
//     cout << "lqfec.size = " << lqfec.size() << endl;
//     for(int i = 0; i < 20; i++)
//     {
//         cout << lqfec.front() << " ";
//         lqfec.pop();
//     }
// }