#include"../case/5-12.h"

template<class T>
class vectorListWithMerge:public vectorList<T>
{
    public:
        vectorListWithMerge(int initialCapacity = 10):vectorList<T>(initialCapacity){}
        void merge(const vectorListWithMerge<T> &a, const vectorListWithMerge<T> &b);
};

template<class T>
void vectorListWithMerge<T>::merge(const vectorListWithMerge<T> &a, const vectorListWithMerge<T> &b)
{
    int i, j, k;
    i = j = k = 0;
    this->element->reserve(a.size()+b.size());

    if(a.size() == b.size() && a.size() == 0) return;
    else if(a.size() == 0 && b.size() != 0 || b.size() == 0)
    {
        while(k < max(a.size(), b.size()))
        {
            this->insert(k, a.size() > b.size() ? a.get(k) : b.get(k));//永远不要去假设++运算符的计算时机！！！！
            k++;
        }
        return;
    }
    // (*(this->element)).reserve(a.size(), b.size());
    
    for(; k < 2*std::min(a.size(), b.size()) && i < a.size() && j < b.size();)
    {
        if( a.get(i) == b.get(j))
        {
            int theLess = i > j ? b.get(j++) : a.get(i++);
            this->insert(k++, theLess);
            continue;
        }
        T theLess = a.get(i) > b.get(j) ? b.get(j++) : a.get(i++);
        this->insert(k++, theLess);
    }
    while(k < this->capacity())
    {

        // T theElement = a.size() > b.size()? a.get(i++) : b.get(j++);
        while(i != a.size())
            this->insert(k++, a.get(i++));
        while(j != b.size())
            this->insert(k++, b.get(j++));
    }
}

int main()
{
    vectorListWithMerge<int> a, b, c;
    for(int i = 0; i < 5; i++)
    {
        a.insert(i, i+1);
        b.insert(i, i);
    }
    try{
    c.merge(a, b);
    }catch(IllegalParameter ip){ip.outputMessage();}
    // std::cout << a.get(4);
    // std::cout << a << std::endl << b << std::endl << c;
    std::cout << c;
}