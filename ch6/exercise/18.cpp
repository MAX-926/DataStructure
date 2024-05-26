#include"../case/6-2.h"

// template<class T>
// class chainListWithMeld:public chain<T>
// {
//     public:
//         chainListWithMeld(int initialCapacity = 10):chain<T>(initialCapacity){}
//         void meld(chain<T> &a, chain<T> &b);
// };

// template<class T>
// void chainListWithMeld<T>::meld(chain<T> &a, chain<T> &b)
// {
//     //將表清空
//     while(this->firstNode)
//     {
//         chainNode<T>* nextNode = this->firstNode->next;
//         delete this->firstNode;
//         this->firstNode = nextNode;
//     }
//     //轉接a表到當前對象firstNode
//     this->firstNode = a.firstNode;
//     this->listSize = a.listSize;
//     //a表置空
//     a.firstNode = NULL;
//     //插入b表元素
//     //若b表為空
//     if(b.size() == 0)
//         return;
//     //b表非空
//     chainNode<T>* currentA = this->firstNode;
//     chainNode<T>* currentB = b.firstNode;
//     //確定插入情況
//     double insertionLength = (this->listSize)-1;
//     for(int i = 0; i < insertionLength; i++)
//     {
//         chainNode<T>* nextA = currentA->next, *nextB = currentB->next;
//         currentA->next = currentB;
//         currentA->next->next = nextA;
//         currentB = nextB;
//         //A步進2步
//         currentA = currentA->next->next;
//     }
//     if(currentB)
//     {
//         currentA->next->next = currentB;
//         b.firstNode = NULL;
//     }
//     this->listSize += b.size();
// }

int main()
{
    chain<int> c;
    chain<int> a, b;
    // a.insert(0, 1);
    for(int i = 0; i < 10; i++)
    {
        a.insert(i, i+1);
        // b.insert(i, i+100);
        c.insert(i ,0);
    }
    for(int i = 0; i < 5; i++)
    {
        // a.insert(i, i+1);
        b.insert(i, i+100);
        // c.insert(i ,0);
    }
    cout << "a:" << a << endl << "b:"<< b << endl << "c:" << c << endl;
    c.meld(a, b);
    // cout << c;
    cout << "a:" << a << endl << "b:"<< b << endl << "c:" << c << endl;
}