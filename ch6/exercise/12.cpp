#include"../../ch5/case/5-3.h"
#include"../case/6-2.h"

template<class T>
arrayList<T>*  converse(const chain<T> &theList)//O(listSize)
{
    auto it = theList.begin();
    arrayList<T>* targetList = new arrayList<T>;
    int i = 0;
    while(it != theList.end())
    {
        targetList->insert(i, *(it++));
        i++;
    }
    // for(int i = 0; i < theList.size(); i++)
        // targetList->insert(i, theList.get(i));
    return targetList;
}

int main()
{
    chain<int> x;
    for(int i = 0; i < 10; i++)
        x.insert(i, i);
    arrayList<int>* targetChain = converse(x);
    cout << x << endl << *targetChain;
}