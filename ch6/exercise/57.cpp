//listLinker

#include"55.cpp"
#include"../../Tool.h"

template<class T>
void doubleCircularListWithHeader<T>::listLinker(doubleCircularListWithHeader<T> &theDCLWH)
{
    if(theDCLWH.header->next == header) return;
    else
    {
        header->previous->next = theDCLWH.header->next;
        theDCLWH.header->next->previous = header->previous;
        listSize += theDCLWH.listSize;
        theDCLWH.header->previous->next = header;
        header->previous = theDCLWH.header->previous;
        //initialization of theDCLWH:
        theDCLWH.header->next = theDCLWH.header;
        theDCLWH.header->previous = theDCLWH.header;
        theDCLWH.listSize = 0;
        return;
    }
}

// int main()
// {
//     doubleCircularListWithHeader<int> a, b;
//     for(int i = 0; i < 5; i++)
//     {
//         a.insert(i, i);
//         b.insert(i, i+10);
//     }
//     std::cout << "a: " << a << std::endl << "b: " << b << std::endl;
//     a.listLinker(b);
//     std::cout << "a: " << a << std::endl << "b: " << b << std::endl;
//     __HeaderList_fluencyTest<doubleCircularListWithHeader<int>>(a);
//     std::cout << std::endl;
//     a.push_back(26);
//     std::cout << "a: " << a << std::endl << "b: " << b << std::endl;

//     a.insert(0, 26);
//     std::cout << "a: " << a << std::endl << "b: " << b << std::endl;
//     a.erase(0);
//     a.erase(a.size()-1);
//     __HeaderList_fluencyTest<doubleCircularListWithHeader<int>>(a);

// }