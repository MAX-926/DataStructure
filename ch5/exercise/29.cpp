#include"../case/5-3.h"

template<class T>
class arrayListWithMerge:public arrayList<T>
{
    public:
        arrayListWithMerge(int initialCapacity = 10):arrayList<T>(initialCapacity){}
        // const arrayListWithMerge<T> &a
        void merge(const arrayListWithMerge<T> &a, const arrayListWithMerge<T> &b);
        T* getEle() const{ return this->element;}
};

template<class T>
void arrayListWithMerge<T>::merge(const arrayListWithMerge<T> &a, const arrayListWithMerge<T> &b)
{
    int newLength = a.size() + b.size();
    delete [](this->element);
    (this->element) = new T[newLength];
    this->arrayLength = newLength;
    int i, indexA = 0, indexB = 0;
    for(i = 0; i < newLength && indexA < a.size() && indexB < b.size(); i++, (this->listSize)++)
        // (this->element)[i] = (a.element[indexA] <= b.element[indexB]  ? a.element[indexB++] : b.element[indexA++]);

        {
            if(a.element[indexA] > b.element[indexB])
            {
                (this->element)[i] = b.element[indexB++];
            }
            else if(a.element[indexA] < b.element[indexB])
            {
                (this->element)[i] = a.element[indexA++];
            }
            else
            {
                if(indexA > indexB)
                {
                    (this->element)[i] = b.element[indexB++];
                }
                else
                {
                    (this->element)[i] = a.element[indexA++];
                }
            }
        }
    for( ; i < newLength; i++, (this->listSize)++)
        (this->element)[i] = (a.size() - b.size() > 0 ? a.element[indexA++] : b.element[indexB++]);
}

int main()
{
    arrayListWithMerge<int> a, b, c, d(10);
    for(int i = 0; i < 5; i++)
    a.insert(i, i+1);
    for(int i = 0; i < 5; i++)
    b.insert(i, i+2);
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    c.merge(a, b);
    std::cout << c << std::endl;
    // std::merge(a.getEle(), a.getEle() + a.size(), b.getEle(), b.getEle() + b.size(), d.getEle() + d.size());
    // std::cout << d << std::endl;
}