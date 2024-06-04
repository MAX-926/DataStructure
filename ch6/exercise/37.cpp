//删除一个节点可以用节点的后继数据覆盖当前节点，尔后删除后继节点
#include"29.cpp"
//链表的状态：firsNode、lastNode、listSize
//删除最后一个节点要注意处理链表的状态
template<class T>
void circularList<T>::erase_new(int theIndex)//O(theIndex)
{
    checkIndex(theIndex);
    if(theIndex == 0)//O(1)
    {
        if(listSize == 1)
        {
            delete firstNode;
            firstNode = 0;
            lastNode = 0;
            --listSize;
            return;
        }
        chainNode<T>* nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
        lastNode->next = firstNode;
        --listSize;
        return;
    }
    chainNode<T>* x = firstNode;
    chainNode<T>* previous;
    for(int i = 0; i < theIndex; i++)//O(theIndex)
    {
        previous = x;
        x = x->next;
    }
    x->element = x->next->element;
    chainNode<T>* deleteNode = x->next;
    x->next = x->next->next;
    delete deleteNode;
    --listSize;
    if(theIndex == listSize) 
    {
        lastNode = previous;
        firstNode = x;
    }
}

int main()
{
    circularList<int> x;
    // for(int i = 0; i < 10; i++)
        // x.insert(i, i+1);
    x.insert(0, 26);
    std::cout << x << std::endl;
    // x.erase_new(0);
    // x.push_back(26);
    // x.insert(0, 26);
    std::cout << x << std::endl;
}