#include"../case/6-2.h"

// template<class T>
// void chain<T>::insertSort()
// {
//     if(listSize == 1 || listSize == 0){return;}
//     chainNode<T>* currentNode = firstNode->next;
//     chainNode<T>* previousNode = firstNode;
//     bool moved = false;
//     while(currentNode != NULL)//若当前的节点非表尾时：
//     {
//         moved = false;
//         previousNode = firstNode;
//         chainNode<T>* compareNode = firstNode;//设置链表迭代器
//         while(compareNode != currentNode)
//         {
//             if(compareNode->element > currentNode->element)
//             {
//                 while(previousNode->next != compareNode && previousNode != compareNode)
//                     previousNode = previousNode->next;
//                 // chainNode<T>* nextNode = previousNode->next;
//                 if(previousNode == compareNode)
//                 {
//                     firstNode = currentNode;
//                     currentNode = currentNode->next;
//                     firstNode->next = compareNode;
//                     compareNode->next->next = currentNode;
//                     break;
//                 }
//                 else
//                 {
//                     previousNode->next = currentNode;
//                     currentNode = currentNode->next;
//                     previousNode->next->next = compareNode;
//                     break;
//                 }
//             }
//             else compareNode = compareNode->next;
//         }
//         if(!moved){currentNode = currentNode->next;}
//     }
// }

template<class T>
void chain<T>::insertSort()
{
    if(listSize <= 1){return;}
    chainNode<T>* currentNode = firstNode->next;
    chainNode<T>* compareNode = firstNode;
    chainNode<T>* previousNode = firstNode;
    chainNode<T>* lastNode = firstNode;
    bool moved = false;
    while (currentNode != NULL)//若当前待插入的节点不是表尾时
    {
        moved = false;
        previousNode = firstNode;
        compareNode = firstNode;
        while(compareNode != currentNode)
        {
            if(compareNode->element > currentNode->element)
            {
                while(previousNode->next != compareNode && compareNode != previousNode)//O(n):线性开销
                    previousNode = previousNode->next;
                // if(!currentNode->next) previousNode->next = NULL;
                if(previousNode == compareNode)//compareNode == firstNode
                {
                    //寻找表尾节点
                    while(lastNode->next != currentNode){ lastNode = lastNode->next;}//O(n):线性开销
                    firstNode = currentNode;
                    currentNode = currentNode->next;
                    moved = true;
                    firstNode->next = compareNode;
                    lastNode->next = currentNode;
                    break;
                }
                else
                {
                    //寻找尾节点
                    while(lastNode->next != currentNode){lastNode = lastNode->next;}//O(n):线性开销
                    previousNode->next = currentNode;
                    currentNode = currentNode->next;
                    moved = true;
                    previousNode->next->next = compareNode;
                    lastNode->next = currentNode;
                    break;
                }
            }
            else compareNode = compareNode->next;//O(1)
        }
        if(!moved){currentNode = currentNode->next;}//O(1)
    }
}

// int main()
// {
//     chain<int> x;
//     // x.insert(0, 0);
//     // x.insert(1, 5);
//     // x.insert(2, 4);
//     // x.insert(3, 6);
//     cout << x << endl;
//     x.insertSort();
//     cout << x << endl;
// }