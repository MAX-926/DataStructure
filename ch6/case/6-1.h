#ifndef CH6_6_1_H
#define CH6_6_1_H
#include<iostream>
template<class T>
struct chainNode
{
    chainNode(){}
    // chainNode(const T &element = 0){this->element = element;}
    chainNode(const T &element, chainNode<T>* next = nullptr){this->element = element; this->next = next;}
    //Data
    T element;
    //pointer
    chainNode<T>* next;
};
#endif //CH6_6_1_H
