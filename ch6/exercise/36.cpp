#include"29.cpp"

template<class T>
void circularList<T>::split(circularList<T> &a, circularList<T> &b)
{//a中包含c中索引為奇數的元素，b包含其餘元素
    //this鏈表爲空時:
    if(!listSize) return;
    //this鏈表非空時:
    else
    {
        a.clear();
        b.clear();
        //初始化b表頭
        b.firstNode = firstNode;
        firstNode = firstNode->next;
        if(listSize == 1)
        {
            //奇數索引給b鏈表
            //b表的初始化
            b.firstNode->next = b.firstNode;//綁定鏈尾
            b.lastNode = b.firstNode;//設定lastNode
            ++b.listSize;//增值listSize
            //this的處理
            firstNode = 0;
            lastNode = 0;
            --listSize;
            return;
        }
        if(listSize == 2)
        {
            b.firstNode->next = b.firstNode;//綁定鏈尾
            b.lastNode = b.firstNode;//設定lastNode
            ++b.listSize;//增值listSize

            a.firstNode = firstNode;
            a.firstNode->next = a.firstNode;
            a.lastNode = a.firstNode;
            ++a.listSize;
            //初始化this表
            firstNode = 0;
            lastNode = 0;
            listSize -= 2;
            return;
        }
        else//listSize > 2
        {
            b.lastNode = b.firstNode;
            b.lastNode->next = b.firstNode;
            ++b.listSize;
            //初始化a表頭
            a.firstNode = firstNode;
            a.lastNode = a.firstNode;//!!
            firstNode = firstNode->next;
            a.lastNode->next = a.firstNode;
            ++a.listSize;

            int indexThis = 2;
            chainNode<T>* iterA = a.firstNode, *iterB = b.firstNode;
            while(indexThis < listSize)
            {
                if(indexThis % 2 == 0)
                {
                    iterB->next = firstNode;
                    iterB = iterB->next;
                    b.lastNode = iterB;
                    firstNode = firstNode->next;

                    b.lastNode->next = b.firstNode;
                    ++b.listSize;

                    ++indexThis;
                    continue;
                }
                else
                {
                    iterA->next = firstNode;
                    iterA = iterA->next;
                    a.lastNode = iterA;
                    firstNode = firstNode->next;

                    a.lastNode->next = a.firstNode;
                    ++a.listSize;

                    ++indexThis;
                    continue;
                }
            }
        }
        firstNode = 0;
        lastNode = 0;
        listSize = 0;
        return;
    }
}


int main()
{
    circularList<int> a, b, c;
    for(int i = 0; i < 3; i++)
    {
        // a.insert(i, i+1);
        // b.insert(i, i+1);
        c.insert(i, i);
    }
    std::cout << "c:" << c << std::endl;
    c.split(a, b);
    std::cout << "a:" << a << std::endl;
    std::cout << "b:" << b << std::endl;
    std::cout << "c:" << c << std::endl;

    // a.insert(0, 26);
    // b.insert(0, 26);
    // a.push_back(26);
    // b.push_back(26);
    // a.insert(0, 26);
    // b.insert(0, 26);
    // std::cout << "a:" << a.size() << std::endl;
    // std::cout << "b:" << b.size() << std::endl;
    // std::cout << "c:" << c.size() << std::endl;
}