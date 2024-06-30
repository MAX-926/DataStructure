//binSort作为chain的成员方法
#include"6-2.h"
#include"6-16.h"

// template<class T>
// void chain<T>::binSort(int range)
// {//对链表中的节点排序
//     //创建并初始化箱子
//     if(listSize <= 1) return;

//     chain<studentRecord>** bottom, **top;
//     bottom = new chainNode<T>*[range+1];
//     top = new chainNode<T>*[range+1];
//     for(int b = 0; b <= range; b++)
//         bottom[b] = nullptr;
//     //把链表的节点分配到箱子
//     for(; firstNode != nullptr; firstNode = firstNode->next)
//     {//把首节点加到箱子中
//         // bottom[int(firstNode->element)] = firstNode;
//         int theBin = firstNode->element;
//         if(bottom[theBin] == nullptr)
//             bottom[theBin] = top[theBin] = firstNode;
//         else
//         {
//             top[theBin]->next = firstNode;
//             top[theBin] = firstNode;
//         }
//     }
//     //把箱子中的节点收集到有序链表
//     chainNode<T>* y = nullptr;
//     for(int theBin = 0; theBin <= range; theBin++)
//         if(bottom[theBin] != nullptr)
//         {//箱子不空
//             if(y == nullptr)
//                 firstNode = bottom[theBin];
//             else
//                 y->next = bottom[theBin];
//             y = top[theBin];
//         }
//     if(y != nullptr)
//         y->next = nullptr;
    
//     delete []bottom;
//     delete []top;
// }

// template<class T>
// void chain<T>::binSort(int range)
// {
//     chainNode<T>** bottom, **top;
//     bottom = new chainNode<T>*[range+1];
//     top = new chainNode<T>*[range+1];
//     for(int b = 0; b <= range; b++)
//         bottom[b] = nullptr;
//     //将元素放置于指定箱子
//     for(; firstNode != nullptr; firstNode = firstNode->next)
//     {
//         int theBin = firstNode->element;
//         if(bottom[theBin] == nullptr)
//         {
//             bottom[theBin] = top[theBin] = firstNode;
//         }
//         else
//         {
//             //为什么是top不是bottom
//             top[theBin]->next = firstNode;
//             top[theBin] = top[theBin]->next;
//         }
//     }
//     chainNode<T>* y = nullptr;
//     //将箱子中的元素重新分配
//     for(int i = 0; i <= range; i++)
//     {
//         if(bottom[i] != nullptr)
//         {
//             // if(firstNode == nullptr)
//             if(y == nullptr)
//                 firstNode = bottom[i];
//             else
//             {
//                 y->next = bottom[i];
//             }
//             y = top[i];
//         }
//     }
//     if(y != nullptr)
//         y->next = nullptr;

//     delete []top;
//     delete []bottom;
// }

template<class T>
void chain<T>::binSort(int range)
{
    //1.产生箱子
    //2.塞入箱子
    //3.链接箱子
    //清除箱子
    chainNode<T>** bottom, **top;
    bottom = new chainNode<T>*[range+1];
    top = new chainNode<T>*[range+1];
    for(int b = 0; b <= range; b++)
        bottom[b] = nullptr;
    //将元素置于箱子内
    for(; firstNode != nullptr; firstNode = firstNode->next)
    {
        int theBin = firstNode->element;
        if(bottom[theBin] == nullptr)
            bottom[theBin] = top[theBin] = firstNode;
        else
        {
            top[theBin]->next = firstNode;
            top[theBin] = firstNode;
        }
    }
    chainNode<T>* y = nullptr;
    for(int theBin = 0; theBin <= range; theBin++)
    {
        if(bottom[theBin] != nullptr)
        {
            if(y == nullptr)
                firstNode = bottom[theBin];
            else
            {
                y->next = bottom[theBin];
            }
            y = top[theBin];
        }
    }
    if(y != nullptr)
        y->next = nullptr;
    
    delete [] bottom;
    delete [] top;
}

int main()
{
    chain<int> a;
    for(int i = 0; i < 10; i++)
        a.insert(i, 10-i);
    std::cout << "a: " << a << std::endl;
    a.binSort(10);
    std::cout << "a: " << a << std::endl;
}