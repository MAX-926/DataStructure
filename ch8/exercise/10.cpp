//具体类stackWithArrayList，其派生于抽象类stack。这个类具有单个数据成员，其类型为arrayList<T>。评价类derivedArrayStack和stackWithArrayList各自的优点

#include"../case/8-1.h"
#include"../../ch5/case/5-3.h"
#include"../../Tool.h"
#include<sstream>

template<class T>
class stackWithArrayList:stack<T>
{
    public:
        //constructor, copy-constructor and destructor
        stackWithArrayList(int initialCapacity = 10):list(initialCapacity){}
        stackWithArrayList(const stackWithArrayList<T>& swal);
        ~stackWithArrayList(){}
        //ADT methodss:
        bool empty()const{return list.empty();}
        int size()const{return list.size();}
        T& top(){return list.get(size()-1);}//会有性能损失，因为要进行额外多余的下标检查
        void pop()
        {
            if(list.empty())
                throw stackEmpty();
            list.erase(list.size()-1);
        }
        void push(const T& theElement)
        {
            list.insert(list.size(), theElement);
        }
    private:
        arrayList<T> list;//使用组合技巧
};

template<class T>
stackWithArrayList<T>::stackWithArrayList(const stackWithArrayList<T>& theSWAL):list(theSWAL.list){}

int main()
{
    stackWithArrayList<int> s;
    for(int i = 0; i < 5; i++)
        s.push(i);
    cout << s.size() << endl;
    // for(int i = 0; i < 5; i++)
    // {
    //     cout << s.top();
    //     s.pop();
    // }
    // cout << s.size() << endl;
    cout << s.empty() << endl;
    cout << s.top() << endl;
}

//评价derivedArrayStack和stackWithArrayList各自的优点
//二者就代码编写而言均较为简洁
//当需要将stack视作arrayList类型时，derivedArrayStack有天然的优势。
//当arrayList的代码更动时，derivedArrayList的代码有可能需要更动，增加了维护的难度