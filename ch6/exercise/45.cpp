#include"43.cpp"

template<class T>
void doublyLinkedList<T>::reverse()//O(n),相较于单向链表的reverse而言，复杂度降低不少（因为双向链表的节点的状态相较于单向链表而言更多，有更详细的记录。所以处理问题更简单吗？？）
{
    // bdChainNode<T>* temp = firstNode;
    // firstNode = lastNode;
    // lastNode = temp;
    //不能单纯的交换收尾节点，因为这样做，即使链条仍然完整，但其中每个节点的的next与previous没有更新，这样不能匹配其它ADT methods的处理逻辑（如output函数，将线性标表的元素从firstNode插入到lastNode，通过next指针步进）
    bdChainNode<T>* currentNodeLeft = firstNode, *currentNodeRight;
    int leftIndex = listSize / 2 - 1, rightIndex; 
    if(listSize % 2 == 0) rightIndex = leftIndex+1;
    else rightIndex = leftIndex + 2;
    for(int i = 0; i < leftIndex; i++)//o(listSize/2)
        currentNodeLeft = currentNodeLeft->next;
    if(listSize % 2 == 0) currentNodeRight = currentNodeLeft->next;
    else currentNodeRight = currentNodeLeft->next->next;
    //开始倒序
    while(currentNodeLeft != NULL)//O(listSize/2)
    {
        std::swap(currentNodeLeft->element, currentNodeRight->element);
        currentNodeLeft = currentNodeLeft->previous;
        currentNodeRight = currentNodeRight->next;
    }
    return;
}

template<class T>
void reverse(doublyLinkedList<T> &theDLL)//O(ls)
{
    // theDLL.reverse();
    //或使用iterator
    auto iterL = theDLL.begin(), iterR = theDLL.begin();
    int ls = theDLL.size();
    int leftIndex = ls / 2 - 1;
    for(int i = 0; i < leftIndex; i++)
    {
        iterL++;
        iterR++;
    }
    if(ls % 2 == 0) iterR++;
    else
    {
        iterR++;
        iterR++;
    }
    while(iterL != theDLL.begin())
    {
        std::swap(*(iterL--), *(iterR++));
    }
    std::swap(*iterL, *iterR);
}

int main()
{
    doublyLinkedList<int> x;
    for(int i = 0; i < 9; i++)
        x.insert(i, i+1);
    std::cout << "x:" << x << std::endl;
    // x.reverse();
    reverse(x);
    std::cout << "x:" << x << std::endl;
    x.push_back(26);
    x.insert(0, 26);
    x.erase(0);
    x.erase(9);
    std::cout << "x:" << x << std::endl;
}