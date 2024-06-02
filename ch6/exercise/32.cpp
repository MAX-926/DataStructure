//为循环链表实现meld函数
#include"29.cpp"

template<class T>
class circularListWithMeld:public circularList<T>
{
    public:
        circularListWithMeld():circularList<T>(){}
        void meld(const circularListWithMeld<T> &a, const circularListWithMeld<T> &b);
};

template<class T>
void circularListWithMeld<T>::meld(const circularListWithMeld<T> &a, const circularListWithMeld<T> &b)//O(listSize + a.listSize + b.listSize)
{
    if(!(a.listSize + b.listSize))//O(1) 
        return;
    if(this->listSize != 0)//O(listSize)
        this->clear();
    //a或b其中一個為空表時：
    if(!a.listSize)//O(a.listSize)
    {
        chainNode<T>* currentNode = b.firstNode;
        while(currentNode->next != b.firstNode)
        {
            this->push_back(currentNode->element);
            currentNode = currentNode->next;
        }
        this->push_back(currentNode->element);
        return;
    }
    if(!b.listSize)//O(b.listSize)
    {
        chainNode<T>* currentNode = a.firstNode;
        while(currentNode->next != a.firstNode)
        {
            this->push_back(currentNode->element);//O(1)
            currentNode = currentNode->next;
        }
        this->push_back(currentNode->element);
        return;
    }
    //a,b皆非空時：
    chainNode<T>* currentNodeA = a.firstNode, *currentNodeB = b.firstNode;
    bool cross = true;
    int crossGetLen = 2*std::min(a.listSize, b.listSize);
    for(int i = 0; i < crossGetLen; i++)//O(crossGetLen)
    {
        if(cross)
        {
            this->push_back(currentNodeA->element);
            currentNodeA = currentNodeA->next;
            cross = false;
            continue;
        }
        else
        {
            this->push_back(currentNodeB->element);
            currentNodeB = currentNodeB->next;
            cross = true;
            continue;
        }
    }
    while(currentNodeA != a.firstNode)
    {
        this->push_back(currentNodeA->element);
        currentNodeA = currentNodeA->next;
    }
    while(currentNodeB != b.firstNode)
    {
        this->push_back(currentNodeB->element);
        currentNodeB = currentNodeB->next;
    }
}

int main()
{
    circularListWithMeld<int> a, b, c;
    a.push_back(26);
    std::cout << a;
    // for(int i = 0; i < 3; i++)
    // {
    //     a.insert(i, 'a');
    // }
    // for(int i = 0; i < 4; i++)
    // {
    //     b.insert(i ,'b');
    // }
    // std::cout << "a:" << a << std::endl << "b:" << b << std::endl;
    // c.meld(a, b);
    // std::cout << "a:" << a << std::endl << "b:" << b << std::endl;
    // std::cout << "c:" << c << std::endl;
}