#include"../case/5-3.h"

template<class T>
class arrayListWithMeld:public arrayList<T>
{
    public:
        arrayListWithMeld(int initialCapacity = 10):arrayList<T>(initialCapacity){}
        void meld(const arrayListWithMeld<T> &a, const arrayListWithMeld<T> &b);
        void func();
};

template<class T>
void arrayListWithMeld<T>::meld(const arrayListWithMeld<T> &a, const arrayListWithMeld<T> &b)
{
    int newLength = a.size()+b.size(), indexA = 0, indexB = 0;// O(1)
    delete [](this->element);//O(1) or O(listSize)
    (this->element) = new T[newLength];//O(newLength)
    this->arrayLength = newLength;//O(1)
    int i;//O(1)
    for(i = 0; i < newLength && indexA < a.size() && indexB < b.size(); i++, (this->listSize)++)//O(max(a.size, b.size)+1)
        (this->element)[i] = (i%2 == 0 ? a.element[indexA++] : b.element[indexB++]);//O(max(a.size, b.size))
        // this->insert(i, (i%2 == 0 ? a.element[indexA++] : b.element[indexB++]));
    for(; i < newLength; i++, (this->listSize)++)//O(newLength - max(a.size, b.size)+1)
        (this->element)[i] = (a.size() - b.size() >  0 ? a.element[indexA++] : b.element[indexB++]);//O(newLength - max(a.size, b.size))   爲什麽不行？？ 因爲沒有在循環結構中隨著新數據的插入而增加this->listSize的值
        // this->insert(i, (a.size() - b.size() >  0 ? a.element[indexA++] : b.element[indexB++]));// 爲什麽表達式要大於0？ 儅a.size() == b.size()時， 最後需要輸出b.last，若取等號則最後會輸出a.last,造成錯誤 
}//total: O(newLength-max(a.size, b,size) +1 + max(a.size, b.size) + 1 + ...) = O(newLength), listSize與newLength同階， 儅a,size與b,size足夠大時，newLength = a.size+b.size足夠大，所以算法的時間複雜度表現為O(newLength)

template<class T>
void arrayListWithMeld<T>::func()
{
    for(int i = 0; i < this->listSize; i++)
        std::cout << (this->element)[i] << " ";
}

int main()
{
    try
    {
    arrayListWithMeld<int> a(5), b(5), c;
    for(int i = 0; i < 5; i++)
    {
        b.insert(i, i);
    }
    for(int i = 0; i < 8; i++)
        a.insert(i, i+10);
    // std::cout << b.size();
    c.meld(a, b);
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;
    }catch(IllegalParameter ip){ip.outputMessage();}
}