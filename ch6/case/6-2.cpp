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

#include"6-2.h"

template<class T>
void chain<T>::checkIndex(int theIndex)const
{
    if(theIndex < 0 || theIndex >= listSize)
    {
        ostringstream s;
        s << "theIndex = " << theIndex << " listSize = " << listSize;
        throw IllegalParameter(s.str());
    }
}


template<class T>
chain<T>::chain(int initialCapacity)
{
    if(initialCapacity < 1)
    {
        ostringstream s;
        s << " initialCapacity = " << initialCapacity << " Must be > 0";
        throw IllegalParameter(s.str());
    }
    listSize = 0;
    firstNode = NULL;
}

template<class T>
chain<T>::chain(const chain<T> &theChain)
{
    listSize = theChain.listSize;
    if(listSize == 0){firstNode = NULL;return;}

    chainNode<T>* current = firstNode, *c_current = theChain.firstNode;
    firstNode = new chainNode<T>(c_current->element, NULL);
    c_current = c_current->next;
    while(c_current != NULL)
    {
        current->next = new chainNode<T>(c_current->element);
        current = current->next;
        c_current = c_current->next;
        // current->next = NULL;
    }
    current->next = NULL;
}

template<class T>
chain<T>::~chain()
{
    while(firstNode != NULL)
    {
        chainNode<T>* tmp = firstNode->next;
        delete firstNode;
        firstNode = tmp;
    }
}

template<class T>
T& chain<T>::get(int theIndex)const
{
    checkIndex(theIndex);
    chainNode<T>* current = firstNode;
    int i = 0;
    while(i != theIndex)
    {
        current = current->next;
        i++;
    }
    return current->element;
}

template<class T>
int chain<T>::indexOf(const T &theElement)const
{
    chainNode<T>* current = firstNode;
    int i = 0;
    // while(current->element != theElement && i < listSize)
    while(current->element != theElement && current != NULL)
    {
        i++;
        current = current->next;
    }
    // if(i == listSize) return -1;
    if(current == NULL) return -1;
    return i;
}



// template<class T>
// void chain<T>::insert(int theIndex, const T& theElement)
// {// Insert theElement so that its index is theIndex.
//    if (theIndex < 0 || theIndex > listSize)
//    {// invalid index
//       ostringstream s;
//       s << "index = " << theIndex << " size = " << listSize;
//       throw IllegalParameter(s.str());
//    }

//    if (theIndex == 0)
//       // insert at front
//       firstNode = new chainNode<T>(theElement, firstNode);
//    else
//    {  // find predecessor of new element
//       chainNode<T>* p = firstNode;
//       for (int i = 0; i < theIndex - 1; i++)
//          p = p->next;
   
//       // insert after p
//       p->next = new chainNode<T>(theElement, p->next);
//    }
//    listSize++;
// }

template<class T>
void chain<T>::insert(int theIndex, const T& theElement)
{
    if(theIndex < 0 || theIndex > listSize)
    {       
        ostringstream s;
        s << "theIndex = " << theIndex << " listSize = " << listSize;
        throw IllegalParameter(s.str());
    }
    if(theIndex == 0)
    {
        firstNode = new chainNode<T>(theElement, firstNode);
        ++listSize;
        return;
    }
    else
    {
        chainNode<T>* current = firstNode, *front = current->next;
        int i = 0;
        while(i != theIndex-1)
        {
            current = current->next;
            front = front->next;
            i++;
        }
        current->next = new chainNode<T>(theElement, front);
        listSize++;
    }
}


template<class T>
void chain<T>::erase(int theIndex)
{
    checkIndex(theIndex);
    chainNode<T>* deleteNode;
    if(theIndex == 0)
    {
        deleteNode = firstNode;
        firstNode = firstNode->next;
    }
    else
    {
        chainNode<T>* current = firstNode;
        for(int i = 0; i < theIndex-1; i++)
            current = current->next;
        deleteNode = current->next;
        current->next = current->next->next;
    }
    delete deleteNode;
    listSize--;
}

// template<class T>
// void chain<T>::erase(int theIndex)
// {
//     checkIndex(theIndex);
//     chainNode<T>* current = firstNode, *front = current->next;
//     int i = 0;
//     if(theIndex == 0)
//     {
//         firstNode = current->next;
//         delete current;
//         listSize--;
//     }
//     else
//     {
//         while(i != theIndex-1)
//         {
//             current = current->next;
//             front = front->next;
//             i++;
//         }
//         delete current->next;
//         current->next = front;
//         listSize--;
//         return;
//     }
// }

template<class T>
void chain<T>::output(ostream& out)const
{
    chainNode<T>* current = firstNode;
    while(current)
    {
        out << current->element << " ";
        current = current->next;
    }
}


template<class T>
void chain<T>::meld(chain<T> &a, chain<T> &b)
{
    //將表清空
    while(this->firstNode)
    {
        chainNode<T>* nextNode = firstNode->next;
        delete this->firstNode;
        this->firstNode = nextNode;
    }
    //轉接a表到當前對象firstNode
    this->firstNode = a.firstNode;
    this->listSize = a.listSize;
    //a表置空
    a.firstNode = NULL;
    a.listSize = 0;
    // //插入b表元素
    // //若b表為空
    if(b.size() == 0)
        return;
    // //b表非空
    chainNode<T>* currentA = this->firstNode;
    chainNode<T>* currentB = b.firstNode;
    // // //確定插入情況
    double insertionLength = (this->listSize);// WHY??????????????????????????? not listSize-1
    for(int i = 0; i < insertionLength; i++)
    {
        if(!currentB) break;
        chainNode<T>* nextA = currentA->next, *nextB = currentB->next;
        currentA->next = currentB;
        currentB->next = nextA;
        currentB = nextB;
        //A步進2步
        currentA = nextA;
    }
    if(currentB)
    {
        if(this->listSize == 0) this->firstNode = currentB;
        else if(listSize == 1) this->firstNode->next = currentB;
        // else currentA->next->next = currentB;
    }
    b.firstNode = NULL;
    b.listSize = 0;
    this->listSize += b.size();
}

// int main()
// {
//     chain<int> x;
//     for(int i = 0; i < 5; i++)
//         x.insert(i ,i+1);
//     std::cout << x;
// }