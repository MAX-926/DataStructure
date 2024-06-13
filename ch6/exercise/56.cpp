//用带有头节点的链表做reverse
#include"55.cpp"
#include"../../Tool.h"

template<class T>
void reverse(doubleCircularListWithHeader<T> &theDCLWH)
{
    auto iterL = theDCLWH.begin(), iterR = theDCLWH.end();
    int ls = theDCLWH.size();
    for(int i = 0; i < ls / 2; i++)
    {
        std::swap(*(iterL++), *(iterR--));
    }
}

template<class T>
void doubleCircularListWithHeader<T>::reverse()
{
    bdChainNode<T>* iterL = header->next, *iterR = header->previous;
    for(int i = 0; i < listSize / 2; i++)
    {
        std::swap(iterL->element, iterR->element);
        iterL = iterL->next;
        iterR = iterR->previous;
    }
    return;
}

// int main()
// {
//     doubleCircularListWithHeader<int> a;
//     for(int i = 0 ; i < 5; i++)
//         a.insert(i, i);
//     std::cout << "a: " << a << std::endl;
//     std::cout << a.size() << std::endl;
//     a.erase(0);
//     // reverse(a);
//     a.reverse();
//     std::cout << "a: " << a << std::endl;
//     __HeaderList_fluencyTest<doubleCircularListWithHeader<int>>(a);
// }