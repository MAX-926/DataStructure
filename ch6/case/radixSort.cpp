#include"6-2.h"
#include<math.h>
using namespace std;

//assume that the number is between 0~100
template<class T>
void chain<T>::radixSort(int range)
{
    int radix = 10;
    chainNode<T>** bottom, **top;
    bottom = new chainNode<T>*[radix];
    top = new chainNode<T>*[radix];

    // for(int b = 0; b < radix; b++)
    //     bottom[b] = nullptr;
    //range is 10、100、1000...
    int exp = 1;
    int numberOfBinSort = range / radix + 1;
    for(int i = 0; i < numberOfBinSort; i++)//O(numberOfBinSort)
    {
        for(int b = 0; b < radix; b++)//O(radix)
        {
            bottom[b] = nullptr;
            top[b] = nullptr;
        }
        //将数字装入箱子：
        for(; firstNode != nullptr; firstNode = firstNode->next)//O(n)
        {
            int theBin = ((firstNode->element) % (int)pow(radix, exp))/(int)pow(radix, exp-1);
            if(bottom[theBin] == nullptr)
            {
                bottom[theBin] = top[theBin] = firstNode;
            }
            else
            {
                top[theBin]->next = firstNode;
                top[theBin] = firstNode;
            }
        }

        //从箱子中取出数字
        chainNode<T>* y = nullptr;
        for(int theBin = 0; theBin < radix; theBin++)//O(radix)
        {
            if(bottom[theBin] != nullptr)
            {
                if(y == nullptr)
                {
                    firstNode = bottom[theBin];
                }
                else
                {
                    y->next = bottom[theBin];
                }
                y = top[theBin];
            }
        }
        
        if(y != nullptr)
            y->next = nullptr;
        exp++;
    }

    delete []bottom;
    delete []top;
}

int main()
{
    chain<int> a;
    for(int i = 0; i < 10; i++)
    {
        a.insert(i, 105-i);
    }
    std::cout << "a: " << a << std::endl;
    a.radixSort(1000);
    std::cout << "a: " << a << std::endl;
}