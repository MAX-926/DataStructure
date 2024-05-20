#include"../case/5-12.h"

template<class T>
class vectorListWithMeld:public vectorList<T>
{
    public:
        //constructor, copy-constructor, destructor
        vectorListWithMeld(int initialCapacity = 10):vectorList<T>(initialCapacity){}
        ~vectorListWithMeld(){delete this->element;}
        void meld(const vectorListWithMeld<T> &a, const vectorListWithMeld<T> &b);
};

template<class T>
void vectorListWithMeld<T>::meld(const vectorListWithMeld<T> &a, const vectorListWithMeld<T> &b)
{
    // vectorListWithMeld<T> c(a.size()+b.size());
    (*(this->element)).reserve(a.size()+b.size());//O(1) or O(size)? 就算是後者，複雜度依然不變
    int i, j, k;//O(1)
    i = j = k = 0;//O(1)
    for( ; k < 2*std::min(a.size(), b.size());)//掃描綫性表a、b,共計a.size()+b.size()個元素， 所以meld的複雜度為O(a.size()+b.size())
    {
        if(k%2 == 0)//O(1)
            // this->insert(k++, a.get(i++));//尾插 O(1)
            this->insert(k++, (*(a.element))[i++]);
        else
            this->insert(k++, b.get(j++));//尾插 O(1)
    }
    while(1)
    {
        if(max(i, j) == max(a.size(), b.size())) break;//O(1)
        b.size() >= a.size() ? this->insert(k++, b.get(j++)) : this->insert(k++, a.get(i++));//尾插 O(1)
    }
}

int main()
{
    vectorListWithMeld<int> a, b, c;
    for(int i = 0; i < 10; i++)
        a.insert(i, i+1);
    for(int i = 0; i < 10; i++)
    {
        b.insert(i, i+100);
    }

    c.meld(a, b);
    try
    {
    std::cout << a << std::endl << b << std::endl;
    std::cout << c;
    }catch(IllegalParameter ip)
    {ip.outputMessage();}
}
    // vector<int>* vp = new vector<int>;
    // // (*vp).reserve(10);
    // for(int i = 0; i < 5; i++)
    //     (*vp)[i] = i+1;
    // for(int i = 0; i < 5; i++)
    //     std::cout << (*vp)[i];
