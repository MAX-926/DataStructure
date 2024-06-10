// #include"49.h"

// template<class T>
// void doubleCircularList<T>::checkIndex(int theIndex)const//O(1)
// {
//     if(theIndex < 0 || theIndex >= listSize)
//     {
//         std::ostringstream s;
//         s << "theIndex = " << theIndex << " listSize = " << listSize;
//         throw IllegalParameter(s.str());
//     }
// }

// template<class T>
// doubleCircularList<T>::doubleCircularList():extendedLinearList<T>()//O(1)
// {
//     firstNode = NULL;
//     lastNode = NULL;
//     listSize = 0;
// }

// template<class T>
// doubleCircularList<T>::doubleCircularList(const doubleCircularList<T> &theDCL)//O()
// {
//     // clear();//需要做实验，观察调用拷贝构造函数时，若不对预有数据清零，得到的链条会是什么情况？
//     //实验结果：拷贝构造函数会自动把调用的对象的初始element清除
//     // listSize = theDCL.listSize;
//     if(!theDCL.listSize) return;
//     listSize = 0;//对于没有使用到的值，要确保它们不会是脏值!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//     //在这里我就以为listSize有被构造成0，事实上在构造这个对象时， 除了拷贝构造函数，不会有其它的构造函数被调用！！
//     bdChainNode<T>* currentNode = theDCL.firstNode;
//     int theIndex = 0;
//     // while(currentNode != theDCL.lastNode)
//     while(theIndex < theDCL.listSize)
//     {
//         push_back(currentNode->element);//O(1)
//         currentNode = currentNode->next;
//         theIndex++;
//     }
//     return;
// }

// template<class T>
// doubleCircularList<T>::~doubleCircularList()
// {
//     // clear();
//     int i = 0;
//     while(i < listSize)
//     {
//         bdChainNode<T>* deleteNode = firstNode;
//         firstNode = firstNode->next;
//         delete deleteNode;
//         i++;
//     }
//     listSize = 0;
//     firstNode = NULL;
//     lastNode = NULL;
// }

// template<class T>
// T& doubleCircularList<T>::get(int theIndex)const
// {
//     checkIndex(theIndex);
//     bdChainNode<T>* currentNode = firstNode;
//     for(int i = 0; i < theIndex; i++)
//         currentNode = currentNode->next;
//     return currentNode->element;
// }

// template<class T>
// int doubleCircularList<T>::indexOf(const T &theElement)const
// {
//     if(!listSize) return -1;
//     else
//     {
//         bdChainNode<T>* currentNode = firstNode;
//         int theIndex = 0;
//         for(; currentNode->element != theElement && theIndex < listSize; theIndex++)
//             currentNode = currentNode->next;
//         if(theIndex == listSize) return -1;
//         else return theIndex;
//     }
// }

// template<class T>
// void doubleCircularList<T>::insert(int theIndex, const T &theElement)
// {
//     if(theIndex < 0 || theIndex > listSize)
//     {
//         std::ostringstream s;
//         s << "theIndex = " << theIndex << " listSize = " << listSize;
//         throw IllegalParameter(s.str());
//     }
//     if(!listSize)
//     {
//         firstNode = new bdChainNode<T>(theElement, NULL, NULL);
//         lastNode = firstNode;
//         lastNode->next = firstNode;
//         firstNode->previous = lastNode;
//         ++listSize;
//         return;
//     }
//     else
//     {
//         if(theIndex == 0)
//         {
//             firstNode = new bdChainNode<T>(theElement, firstNode, lastNode);
//             firstNode->next->previous = firstNode;
//             lastNode->next = firstNode;
//             ++listSize;
//             return;
//         }
//         else if(theIndex == listSize)
//         {
//             lastNode->next = new bdChainNode<T>(theElement, firstNode, lastNode);
//             lastNode = lastNode->next;
//             firstNode->previous = lastNode;
//             ++listSize;
//             return;
//         }
//         else
//         {
//             bdChainNode<T>* currentNode = firstNode;
//             for(int i = 0; i < theIndex - 1; i++)
//                 currentNode = currentNode->next;
//             currentNode->next = new bdChainNode<T>(theElement, currentNode->next, currentNode);
//             currentNode->next->next->previous = currentNode->next;
//             listSize++;
//             return;
//         }
//     }
// }

// template<class T>
// void doubleCircularList<T>::erase(int theIndex)
// {
//     checkIndex(theIndex);
//     bdChainNode<T>* currentNode = firstNode;
//     if(listSize == 1)
//     {
//         delete firstNode;
//         --listSize;
//         firstNode = NULL;
//         lastNode = NULL;
//         return;
//     }
//     else
//     {
//         if(theIndex == 0)
//         {
//             bdChainNode<T>* deleteNode = firstNode;
//             firstNode = firstNode->next;
//             firstNode->previous = lastNode;
//             lastNode->next = firstNode;
//             delete deleteNode;
//             --listSize;
//             return;
//         }
//         for(int i = 0; i < theIndex - 1; i++)
//             currentNode = currentNode->next;
//         bdChainNode<T>* deleteNode = currentNode->next;
//         currentNode->next = deleteNode->next;
//         deleteNode->next->previous = currentNode;
//         delete deleteNode;
//         if(theIndex == listSize-1)
//         {
//             lastNode = currentNode;
//         }
//         --listSize;
//         return;
//     }
// }

// template<class T>
// void doubleCircularList<T>::push_back(const T &theElement)
// {
//     if(!listSize)
//     {
//         firstNode = new bdChainNode<T>(theElement, NULL, NULL);
//         firstNode->next = firstNode;
//         firstNode->previous = firstNode;
//         lastNode = firstNode;
//         ++listSize;
//         return;
//     }
//     lastNode->next = new bdChainNode<T>(theElement, firstNode, lastNode);
//     lastNode = lastNode->next;
//     firstNode->previous = lastNode;
//     ++listSize;
//     return;
// }

// template<class T>
// void doubleCircularList<T>::clear()
// {
//     if(!listSize) return;
//     int ls = listSize;
//     for(int i = 0; i < ls; i++)
//     {
//         bdChainNode<T>* deleteNode = firstNode;
//         firstNode = firstNode->next;
//         std::cout << "delete Node: " << deleteNode->element << std::endl;
//         delete deleteNode;
//         listSize--;
//     }
//     firstNode = NULL;
//     lastNode = NULL;
//     // listSize = 0;
//     return;
// }

// template<class T>
// void doubleCircularList<T>::output(std::ostream& out)const
// {
//     if(!listSize)
//     {
//         out << "";
//         return;
//     }
//     bdChainNode<T>* currentNode = firstNode;
//     for(int i = 0; i < listSize; i++)
//     {
//         out << currentNode->element << " ";
//         currentNode = currentNode->next;
//     }
//     return;
// }
