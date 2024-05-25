#include"../case/6-2.h"
#include<vector>
using namespace std;

template<class T>
class chainListWithLastIndexOf:public chain<T>
{
    public:
        chainListWithLastIndexOf(int initialCapacity = 10):chain<T>(initialCapacity){}     
        int lastIndexOf(const T &element)const;
};

template<class T>
int chainListWithLastIndexOf<T>::lastIndexOf(const T &element)const
{
    vector<int> indexContainer;
    chainNode<T>* current = (this->firstNode);
    int index = 0;
    while(current)
    {
        if(current->element == element)
            indexContainer.push_back(index);
        ++index;
        current = current->next;
    }
    if(indexContainer.empty()) return -1;
    return *(indexContainer.end()-1);
}

int main()
{
    chainListWithLastIndexOf<int> x;
    // for(int i = 0; i < 10; i++)
    //     x.insert(i, i+1);
    cout << x << endl;
    // x.insert(10, 26);
    x.insert(0, 26);
    // cout << x << endl;
    cout << x.lastIndexOf(26);
}