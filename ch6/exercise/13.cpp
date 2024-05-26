#include"../case/6-2.h"
#include"../../ch5/case/5-3.h"

template<class T>
class chainListWithConverser:public chain<T>
{
    public:
        chainListWithConverser(int initialCapacity = 10):chain<T>(initialCapacity){}
        void fromList(const arrayList<T> &theList);
        arrayList<T>* toList()const;
};

template<class T>
void chainListWithConverser<T>::fromList(const arrayList<T> &theList)
{
    int theListSize = theList.size();
    if(theListSize == 0)//O(chainListSize)
    {
        while (this->firstNode)
        {
            chainNode<T>* nextNode = (this->firstNode)->next;
            delete (this->firstNode);
            (this->firstNode) = nextNode;
        }
        this->listSize = 0;
        this->firstNode = NULL;
        return;
    }
    else
    {
        if(theListSize <= this->listSize)//O(chainListSize)
        {
            chainNode<T>* current = (this->firstNode);
            int i;
            for(i = 0; i < theListSize-1; i++)
            {
                current->element = theList.get(i);
                current = current->next;
            }
            current->element = theList.get(i);
            while(current->next)
            {
                chainNode<T>* nextNode = current->next->next;
                delete current->next;
                current->next = nextNode;
            }
            current->next = NULL;
            this->listSize = theListSize;
            return;
        }
        else//O(theListSize)
        {
            chainNode<T>* current = this->firstNode;
            chainNode<T>* previous;
            for(int i = 0; i < theListSize; i++)
            {
                if(!current)
                {
                    current = new chainNode<T>(0, NULL);
                    this->firstNode = current;//要記得更新firstNode的值！！！
                }
                current->element = theList.get(i);
                previous = current;
                if(!(current = current->next))
                {
                    previous->next = new chainNode<T>(0, NULL);
                    current = previous->next;
                }
            }
            delete previous->next;
            previous->next = NULL;
            this->listSize  = theListSize;
            return;
        }
    }
}


template<class T>
arrayList<T>* chainListWithConverser<T>::toList()const//O(listSize)
{
    arrayList<T>* targetList = new arrayList<T>;
    chainNode<T>* current = this->firstNode;
    int i = 0;
    while(current)
    {
        targetList->insert(i++, current->element);
        current = current->next;
    }
    return targetList;
}

int main()
{
    chainListWithConverser<int> x;
    arrayList<int> y;
    for(int i = 0; i < 0; i++)
    {
        x.insert(i, i+1);
        // y.insert(i, i+100);//x.size == y.size
    }
    for(int i = 0; i < 2; i++)
    {
        y.insert(i, i+5);
    }
    // y不赋值,x赋值 y < x
    // y.insert(0, 1);
    cout << "x:";
    cout << x << endl;
    cout << "y:";
    cout << y << endl;
    x.fromList(y);
    cout << "after fromList(y):" << endl;
    cout << "x:";
    cout << x << endl;
    cout << "x.toList():" << endl;
    cout << "x:" << *(x.toList());
}