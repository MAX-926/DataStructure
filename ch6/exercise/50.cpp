#include"49.h"

template<class T>
void reverse(doubleCircularList<T> &theDCL)//O(listSize)
{
    int ls = theDCL.size();
    if(ls < 2) return;//O(1)
    auto iterL = theDCL.begin(), iterR = theDCL.begin();
    for(int i = 0; i < ls / 2 - 1; i++)//让指针停在正确的索引上
    {
        iterL++;
        iterR++;
    }
    if(ls % 2 == 0)
        iterR++;
    else
    {
        iterR++;
        iterR++;
    }
    for(int i = 0; i < ls / 2; i++)//正确的处理元素的个数
        std::swap(*(iterL--), *(iterR++));//O(1)
    return;
}

template<class T>
void doubleCircularList<T>::reverse()//O(listSize)
{
    if(listSize < 2) return;//O(1)
    bdChainNode<T>* currentL = firstNode, *currentR = firstNode;
    for(int i = 0; i < listSize / 2 - 1; i++)
    {
        currentL = currentL->next;
        currentR = currentR->next;
    }
    if(listSize % 2 == 0)
        currentR = currentR->next;
    else
    {
        currentR = currentR->next;
        currentR = currentR->next;
    }
    for(int i = 0; i < listSize / 2; i++)
    {
        std::swap(currentL->element, currentR->element);
        currentL = currentL->previous;
        currentR = currentR->next;
    }
}

// int main()
// {
//     doubleCircularList<int> a;
//     for(int i = 0; i < 0; i++)
//         a.insert(i, i+1);
//     std::cout << "a: " << a << std::endl;
//     reverse(a);
//     a.reverse();
//     std::cout << "a: " << a << std::endl;
//     auto iterA = a.end();
//     try
//     {
//     // for(int i = 0; i  < 5; i++)
//     //     std::cout << *(iterA--) << " ";
//     std::cout << *iterA;
//     }catch(IllegalParameter ip){ip.outputMessage();}
//     // a.push_back(26);
//     // a.insert(0, 26);
//     // std::cout << "a: " << a << std::endl;
// }