#include"../../ch5/case/5-3.h"
#include"../case/6-2.h"

template<class T>
chain<T>* converse(const arrayList<T> &theList)//O(listSize^2)
{
    chain<T>* targetList = new chain<T>;
    for(int i = 0; i < theList.size(); i++)
        targetList->insert(i, theList.get(i));
    return targetList;
}

int main()
{
    arrayList<int> x;
    // for(int i = 0; i < 10; i++)
    //     x.insert(i, i+1);
    chain<int>* targetChain = converse(x);
    // cout << x << 1 << endl << *targetChain << 1;
}