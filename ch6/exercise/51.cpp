#include"49.cpp"

template<class T>
void doubleCircularList<T>::listLinker(doubleCircularList<T> &theDCL)//O(1)
{
    if(!theDCL.listSize) return;//O(1)
    if(!listSize)//O(1)
    {
        firstNode = theDCL.firstNode;
        listSize = theDCL.listSize;
        lastNode = theDCL.lastNode;
        theDCL.firstNode = NULL;
        theDCL.lastNode = NULL;
        theDCL.listSize = 0;
        return;
    }
    else//O(1)
    {
        lastNode->next = theDCL.firstNode;
        theDCL.firstNode->previous = lastNode;
        lastNode = theDCL.lastNode;
        lastNode->next = firstNode;
        firstNode->previous = lastNode;
        listSize += theDCL.listSize;

        theDCL.listSize = 0;
        theDCL.firstNode = NULL;
        theDCL.lastNode = NULL;
        return;
    }
}

int main()
{
    doubleCircularList<int> a, b;
    for(int i = 0; i < 5; i++)
    {
        // a.insert(i, i+1);
        b.insert(i, i+5);
    }
    std::cout << "a: " << a << std::endl << "b: " << b << std::endl;
    a.listLinker(b);
    std::cout << "a: " << a << std::endl << "b: " << b << std::endl;
    std::cout << "a.size() = " << a.size() <<  std::endl << "b.size() = " << b.size() << std::endl;
}