// #include"6-2.h"
// #include<sstream>

// template<class T>
// chain<T>::chain()
// {
//     // if(initialCapacity < 1)
//     // {
//     //     std::ostringstream s;
//     //     s << "initialCapacity  = " << initialCapacity << " Must be > 0";
//     //     throw IllegalParameter(s.str());
//     // }
//     firstNode = nullptr;
//     listSize = 0;
//     std::cout << "chain() was called" << std::endl;
// }

// template<class T>
// chain<T>::~chain()
// {
//     while(!firstNode)
//     {
//         chainNode<T>* tmp = firstNode->next;
//         delete firstNode;
//         firstNode = tmp;
//         std::cout << "Node deletion operation was called" << std::endl;
//     }
//     std::cout << "~chain() was called" << std::endl;
// }

// template<class T>
// T& chain<T>::get(int theIndex)const
// {
//     checkIndex(theIndex);
//     chainNode<T>* tmp = firstNode;
//     int i = 0;
//     while(1)
//     {
//         if(i == theIndex) return tmp->element;
//         tmp = tmp->next;
//         i++;
//     }
// }

// template<class T>
// int chain<T>::indexOf(const T& element)const
// {
//     chainNode<T>* tmp = firstNode;
//     int i = 0;
//     while(1)
//     {
//         if(i == size()) return -1;
//         if(tmp->element == element) return i;
//         tmp = tmp->next;
//         i++;
//     }
// }

// template<class T>
// void chain<T>::insert(int theIndex, const T& element)
// {
//     if(theIndex < 0 || theIndex > listSize)
//     {
//         std::ostringstream s;
//         s << "theIndex  = " << theIndex << " listSize = " << listSize;
//         throw IllegalParameter(s.str());
//     }
//     int i = 0;
//     chainNode<T>* current = firstNode;
//     // chainNode<T>* back;
//     while(1)
//     {
//         std::cout << "while loop times: " << i << std::endl;
//         if(theIndex == 0)
//         {
//             std::cout << "firstNode insertion operation was called" << std::endl;
//             firstNode = new chainNode<T>(element, firstNode);
//             std::cout << "linearlist[" << theIndex << "] = " << current->element << std::endl;
//             listSize++;
//             return;
//         }
//         // back = current;
//         if(i == theIndex-1)
//         {
//             std::cout << "Node insertion operation was called" << std::endl;
//             chainNode<T>* front = current->next;
//             current->next = new chainNode<T>(element, front);
//             listSize++;
//             std::cout << "linearlist[" << theIndex << "] = " << current->element << std::endl;
//             return;
//         }
//         current = current->next;
//         i++;
//     }
// }

// template<class T>
// void chain<T>::erase(int theIndex)
// {
//     checkIndex(theIndex);
//     chainNode<T>* current = firstNode;
//     int i = 0;
//     while(1)
//     {
//         if(theIndex == 0)
//         {
//             chainNode<T>* front = firstNode->next;
//             delete firstNode;
//             firstNode = front;
//             listSize--;
//             return;
//         }
//         // chainNode<T>* back = current;
//         if(i+1 == theIndex)
//         {
//             // back->next = current->next;
//             chainNode<T>* dNode = current->next;
//             current->next = dNode->next;
//             delete dNode;
//             listSize--;
//             return;
//         }
//         current = current->next;
//         i++;
//     }
// }

// template<class T>
// void chain<T>::checkIndex(int theIndex)const
// {
//     if(theIndex < 0 || theIndex >= listSize)
//     {
//         std::ostringstream s;
//         s << "theIndex = " << theIndex << " listSize = " << listSize;
//         throw IllegalParameter(s.str());
//     }
// }

// template<class T>
// void chain<T>::output(std::ostream & out)const
// // void chain<T>::output()const
// {
//     chainNode<T>* current = firstNode;
//     while(!current)
//     {
//         out << current->element << " ";
//         current = current->next;
//     }
// }