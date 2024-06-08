//开发类doubleCircularList，没有头节点， 实现extendedChain的所有方法
#include"../case/6-11.h"
#include"../case/bidirectionalChainNode.h"
#include<iostream>
#include<sstream>
#include<iterator>

template<class T>
class doubleCircularList:public extendedLinearList<T>
{
    public:
    //constructor、copy-constructor、destructor
        doubleCircularList();
        doubleCircularList(const doubleCircularList<T> &theDCL);
        ~doubleCircularList();
    //ADT methods:
        bool empty()const{return listSize == 0;}
        int size()const{return listSize;}
        T& get(int theIndex)const;
        int indexOf(const T &theElement)const;
        void insert(int theIndex, const T &theElement);
        void erase(int theIndex);
        void push_back(const T &theElement);
        void clear();
        void output(std::ostream& out)const;
        //50.cpp reverse():
        void reverse();
        //51.cpp listLinker():
        void listLinker(doubleCircularList<T> &theDCL);
        //53.cpp meld():
        void meld(doubleCircularList<T> &a, doubleCircularList<T> &b);
        //iterator:
        class iterator
        {
            public:
                //用C++的typedef语句实现双向迭代器
                // typedef std::bidirectional_iterator_tag iterator_category;
                // typedef T value_type;
                // typedef ptrdiff_t difference_type;
                // typedef T* pointer;
                // typedef T& reference;

                //对迭代器可能出现空指针索引的问题！！！！！！！
                iterator(bdChainNode<T>* theNode = 0):node(theNode){}
                //解引用
                T& operator*()const
                {
                    if(node == NULL)
                    {
                        std::ostringstream s;
                        s << "Node = " << (node == NULL ? "NULL" : " uncertain situation");
                        throw IllegalParameter(s.str());
                    }
                    return node->element;
                }
                T* operator->()const
                { 
                    if(node == NULL)
                    {
                        std::ostringstream s;
                        s << "Node = " << (node == NULL ? "NULL" : " uncertain situation");
                        throw IllegalParameter(s.str());
                    }
                    return &node->element;
                }
                //forwards:
                iterator& operator++()
                {
                    if(node == NULL)
                    {
                        std::ostringstream s;
                        s << "Node = " << (node == NULL ? "NULL" : " uncertain situation");
                        throw IllegalParameter(s.str());
                    }
                    node = node->next;
                    return *this;
                }
                iterator operator++(int)
                {
                    if(node == NULL)
                    {
                        std::ostringstream s;
                        s << "Node = " << (node == NULL ? "NULL" : " uncertain situation");
                        throw IllegalParameter(s.str());
                    }
                    iterator old = *this;
                    node = node->next;
                    return old;
                }
                //backwards:
                iterator& operator--()
                {
                    if(node == NULL)
                    {
                        std::ostringstream s;
                        s << "Node = " << (node == NULL ? "NULL" : " uncertain situation");
                        throw IllegalParameter(s.str());
                    }
                    node = node->previous;
                    return *this;
                }
                iterator operator--(int)
                {
                    if(node == NULL)
                    {
                        std::ostringstream s;
                        s << "Node = " << (node == NULL ? "NULL" : " uncertain situation");
                        throw IllegalParameter(s.str());
                    }
                    iterator old = *this;
                    node = node->previous;
                    return old;
                }
                //equalization verify:
                bool operator==(const iterator& theDCL)const{ return theDCL.node == node;}
                bool operator!=(const iterator& theDCL)const{ return theDCL.node != node;}
            protected:
                bdChainNode<T>* node;
        };
        iterator begin()const{return iterator(firstNode);}
        iterator end()const{return iterator(lastNode);}
        // void showFirstNode(){std::cout << "firstNode = " << firstNode << std::endl;}
    protected:
        void checkIndex(int theIndex)const;
        bdChainNode<T>* firstNode;
        bdChainNode<T>* lastNode;
        int listSize;
};

template<class T>
void doubleCircularList<T>::checkIndex(int theIndex)const//O(1)
{
    if(theIndex < 0 || theIndex >= listSize)
    {
        std::ostringstream s;
        s << "theIndex = " << theIndex << " listSize = " << listSize;
        throw IllegalParameter(s.str());
    }
}

template<class T>
std::ostream& operator<<(std::ostream& out, const doubleCircularList<T> &theDCL)//O(output())
{
    theDCL.output(out);
    return out;
}

template<class T>
doubleCircularList<T>::doubleCircularList():extendedLinearList<T>()//O(1)
{
    firstNode = NULL;
    lastNode = NULL;
    listSize = 0;
}

template<class T>
doubleCircularList<T>::doubleCircularList(const doubleCircularList<T> &theDCL)//O()
{
    // clear();//需要做实验，观察调用拷贝构造函数时，若不对预有数据清零，得到的链条会是什么情况？
    //实验结果：拷贝构造函数会自动把调用的对象的初始element清除
    // listSize = theDCL.listSize;
    if(!theDCL.listSize) return;
    listSize = 0;//对于没有使用到的值，要确保它们不会是脏值!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //在这里我就以为listSize有被构造成0，事实上在构造这个对象时， 除了拷贝构造函数，不会有其它的构造函数被调用！！
    bdChainNode<T>* currentNode = theDCL.firstNode;
    int theIndex = 0;
    // while(currentNode != theDCL.lastNode)
    while(theIndex < theDCL.listSize)
    {
        push_back(currentNode->element);//O(1)
        currentNode = currentNode->next;
        theIndex++;
    }
    return;
}

template<class T>
doubleCircularList<T>::~doubleCircularList()
{
    // clear();
    int i = 0;
    while(i < listSize)
    {
        bdChainNode<T>* deleteNode = firstNode;
        firstNode = firstNode->next;
        delete deleteNode;
        i++;
    }
    listSize = 0;
    firstNode = NULL;
    lastNode = NULL;
}

template<class T>
T& doubleCircularList<T>::get(int theIndex)const
{
    checkIndex(theIndex);
    bdChainNode<T>* currentNode = firstNode;
    for(int i = 0; i < theIndex; i++)
        currentNode = currentNode->next;
    return currentNode->element;
}

template<class T>
int doubleCircularList<T>::indexOf(const T &theElement)const
{
    if(!listSize) return -1;
    else
    {
        bdChainNode<T>* currentNode = firstNode;
        int theIndex = 0;
        for(; currentNode->element != theElement && theIndex < listSize; theIndex++)
            currentNode = currentNode->next;
        if(theIndex == listSize) return -1;
        else return theIndex;
    }
}

template<class T>
void doubleCircularList<T>::insert(int theIndex, const T &theElement)
{
    if(theIndex < 0 || theIndex > listSize)
    {
        std::ostringstream s;
        s << "theIndex = " << theIndex << " listSize = " << listSize;
        throw IllegalParameter(s.str());
    }
    if(!listSize)
    {
        firstNode = new bdChainNode<T>(theElement, NULL, NULL);
        lastNode = firstNode;
        lastNode->next = firstNode;
        firstNode->previous = lastNode;
        ++listSize;
        return;
    }
    else
    {
        if(theIndex == 0)
        {
            firstNode = new bdChainNode<T>(theElement, firstNode, lastNode);
            firstNode->next->previous = firstNode;
            lastNode->next = firstNode;
            ++listSize;
            return;
        }
        else if(theIndex == listSize)
        {
            lastNode->next = new bdChainNode<T>(theElement, firstNode, lastNode);
            lastNode = lastNode->next;
            firstNode->previous = lastNode;
            ++listSize;
            return;
        }
        else
        {
            bdChainNode<T>* currentNode = firstNode;
            for(int i = 0; i < theIndex - 1; i++)
                currentNode = currentNode->next;
            currentNode->next = new bdChainNode<T>(theElement, currentNode->next, currentNode);
            currentNode->next->next->previous = currentNode->next;
            listSize++;
            return;
        }
    }
}

template<class T>
void doubleCircularList<T>::erase(int theIndex)
{
    checkIndex(theIndex);
    bdChainNode<T>* currentNode = firstNode;
    if(listSize == 1)
    {
        delete firstNode;
        --listSize;
        firstNode = NULL;
        lastNode = NULL;
        return;
    }
    else
    {
        if(theIndex == 0)
        {
            bdChainNode<T>* deleteNode = firstNode;
            firstNode = firstNode->next;
            firstNode->previous = lastNode;
            lastNode->next = firstNode;
            delete deleteNode;
            --listSize;
            return;
        }
        for(int i = 0; i < theIndex - 1; i++)
            currentNode = currentNode->next;
        bdChainNode<T>* deleteNode = currentNode->next;
        currentNode->next = deleteNode->next;
        deleteNode->next->previous = currentNode;
        delete deleteNode;
        if(theIndex == listSize-1)
        {
            lastNode = currentNode;
        }
        --listSize;
        return;
    }
}

template<class T>
void doubleCircularList<T>::push_back(const T &theElement)
{
    if(!listSize)
    {
        firstNode = new bdChainNode<T>(theElement, NULL, NULL);
        firstNode->next = firstNode;
        firstNode->previous = firstNode;
        lastNode = firstNode;
        ++listSize;
        return;
    }
    lastNode->next = new bdChainNode<T>(theElement, firstNode, lastNode);
    lastNode = lastNode->next;
    firstNode->previous = lastNode;
    ++listSize;
    return;
}

template<class T>
void doubleCircularList<T>::clear()
{
    if(!listSize) return;
    int ls = listSize;
    for(int i = 0; i < ls; i++)
    {
        bdChainNode<T>* deleteNode = firstNode;
        firstNode = firstNode->next;
        std::cout << "delete Node: " << deleteNode->element << std::endl;
        delete deleteNode;
        listSize--;
    }
    firstNode = NULL;
    lastNode = NULL;
    // listSize = 0;
    return;
}

template<class T>
void doubleCircularList<T>::output(std::ostream& out)const
{
    if(!listSize)
    {
        out << "";
        return;
    }
    bdChainNode<T>* currentNode = firstNode;
    for(int i = 0; i < listSize; i++)
    {
        out << currentNode->element << " ";
        currentNode = currentNode->next;
    }
    return;
}

// int main()
// {
//     doubleCircularList<int> a;
//     for(int i = 0; i < 5; i++)
//         a.insert(i, i+1);
//     doubleCircularList<int> b = a;//明确拷贝构造函数的调用时机！！！！！！！！！！！！！！！！
//     std::cout << "a: " << a << "b: " << b << std::endl;
//     auto iterA = a.end(), iterB = b.end();
//     std::cout << "a: ";
//     for(int i = 0; i < 10; i++)
//     {
//         std::cout << *(iterA--) << " ";
//     }
//     std::cout << "\nb: ";
//     for(int i = 0; i < 10; i++)
//     {
//         std::cout << *(iterB--) << " ";
//     }
//     std::cout << std::endl;
//     a.erase(0);
//     std::cout << "a.erase(0) = " << a << std::endl;
//     b.erase(0);
//     std::cout << "b.erase(0) = " << b << std::endl;
//     iterA = a.end();
//     iterB = b.end();
//     std::cout << "a: ";
//     for(int i = 0; i < 10; i++)
//     {
//         std::cout << *(iterA--) << " ";
//     }
//     std::cout << "\nb: ";
//     for(int i = 0; i < 10; i++)
//     {
//         std::cout << *(iterB--) << " ";
//     }
// }

// int main()
// {
//     doubleCircularList<int> a;
//     for(int i = 0; i < 2; i++)
//         a.insert(i, i+1);
//     // for(int i = 0; i < 4; i++)
//     //     b.insert(i, i+1);
//     doubleCircularList<int> b = a;
//     std::cout << "a:" << a << std::endl << "b:" << b << std::endl;
//     // b = a;
//     // std::cout << "b.size() = " << b.size() << std::endl;
//     // c = a;
//     // a.push_back(26);
//     // a.insert(0, 28);
//     // a.insert(5, 25);
//     // a.erase(0);
//     // a.erase(a.size()-1);
//     std::cout << "a:" << a << std::endl << "b:" << b << std::endl;
//     auto iterB = b.end();
//     for(int i = 0; i < b.size(); i++)
//         std::cout << *(iterB--) << " ";
//     std::cout << "b.size() = " << b.size();
//     // std::cout << "a:" << a << std::endl << "b:" << b << std::endl << "c:" << c << std::endl;
//     // a.clear();
//     // a.insert(0, 1);
//     // a.push_back(26);
//     // a.push_back(26);
//     // a.insert(a.size(), 29);
//     // a.insert(1, 15);
//     // a.erase(0);
//     // a.erase(a.size()-1);
//     // std::cout << "a:" << a << std::endl << "b:" << b << std::endl << "c:" << c << std::endl;
//     // std::cout << "a.indexOf(-2) = " << a.indexOf(-2) << std::endl;
//     // std::cout << "a.get(0) = " << a.get(0) << std::endl;
//     // std::cout << "a.size() = " << a.size() << std::endl;
//     // std::cout << "a.empty() = " << a.empty() << std::endl;
//     // std::cout << "a:" << a << std::endl << "b:" << b << std::endl << "c:" << c << std::endl;
//     // auto iterA = a.begin();
// }

// //连通性测试：迭代器iterator进行