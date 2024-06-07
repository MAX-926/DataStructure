#include"43.cpp"

template<class T>
void split(doublyLinkedList<T> &a, doublyLinkedList<T> &b, const doublyLinkedList<T> &c)
{//a中包含索引为奇数的元素，b包含其它元素
    int index = 0;
    int lsC = c.size();
    auto iterC = c.begin();
    while(index < lsC)
    {
        if(index % 2 != 0)
        {
            a.push_back(*(iterC++));
            index++;
        }
        else
        {
            b.push_back(*(iterC++));
            index++;
        }
    }
    return;
}

template<class T>
void doublyLinkedList<T>::split(doublyLinkedList<T> &a, doublyLinkedList<T> &b)
{
    if(!listSize) return;
    b.clear();
    if(listSize < 2)
    {
        b.firstNode = firstNode;
        b.lastNode = b.firstNode;
        ++b.listSize;
        b.firstNode->next;

        firstNode = NULL;
        lastNode = NULL;
        --listSize;
        return;
    }
    a.clear();
    if(listSize < 3)
    {
        //绑定b的首节点
        b.firstNode = firstNode;
        b.lastNode = b.firstNode;

        //firstNode forwards:
        firstNode = firstNode->next;

        b.firstNode->next = NULL;//动公用节点的时候，小心调整next与previous的值
        ++b.listSize;


        //绑定a的首节点
        a.firstNode = firstNode;
        a.lastNode = a.firstNode;
        ++a.listSize;
        a.firstNode->previous = NULL;

        //set thisList
        firstNode = firstNode->next;
        lastNode = firstNode;
        listSize = 0;

        return;
    }
    else
    {
        //绑定b的首节点
        b.firstNode = firstNode;
        b.lastNode = b.firstNode;
        ++b.listSize;

        //firstNode forwards:
        firstNode = firstNode->next;

        //绑定a的首节点
        a.firstNode = firstNode;
        a.lastNode = a.firstNode;
        a.firstNode->previous = NULL;
        ++a.listSize;

        //firsNode forwards:
        firstNode = firstNode->next;

        bdChainNode<T>* headA = a.firstNode, *headB = b.firstNode;
        bool crossed = true;
        while(firstNode != NULL)
        {
            if(crossed)
            {
                b.firstNode->next = firstNode;
                firstNode->previous = b.firstNode;
                b.firstNode = b.firstNode->next;
                firstNode = firstNode->next;
                ++b.listSize;
                crossed = !crossed;
            }
            else
            {
                a.firstNode->next = firstNode;
                firstNode->previous = a.firstNode;
                a.firstNode = a.firstNode->next;
                firstNode = firstNode->next;
                ++a.listSize;
                crossed = !crossed;
            }
        }
        a.lastNode = a.firstNode;
        b.lastNode = b.firstNode;
        a.firstNode = headA;
        b.firstNode = headB;
        a.lastNode->next = NULL;
        b.lastNode->next = NULL;
        lastNode = NULL;
        listSize = 0;
    }
}

int main()
{
    doublyLinkedList<int> a, b, c;
    for(int i = 0; i < 3; i++)
        c.insert(i, i);
    for(int i = 0; i < 5; i++)
    {
        a.insert(i, i+1);
        b.insert(i, i+1);
    }
    std::cout << "a:" << a << std::endl << "b:" << b << std::endl << "c:" << c << std::endl;
    // split(a, b, c);
    c.split(a, b);
    std::cout << "a:" << a << std::endl << "b:" << b << std::endl << "c:" << c << std::endl;
}