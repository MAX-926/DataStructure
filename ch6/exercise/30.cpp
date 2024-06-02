//原地颠倒链表节点元素
#include"29.cpp"

template<class T>
class circularListWithReverse:public circularList<T>
{
    public:
        circularListWithReverse():circularList<T>(){}
        void reverse();
};

template<class T>
void circularListWithReverse<T>::reverse()
{
    chainNode<T>* currentNode = this->firstNode;
    int forwardSteps = this->listSize-1;
    for(int i = 0; i < this->listSize/2; i++)
    {
        chainNode<T>* targetNode = this->firstNode;
        for(int j = 0; j < forwardSteps; j++)
            targetNode = targetNode->next;//1, 2, 3, 4, 5, 6, 7, 8, 9, 10
        std::swap(currentNode->element, targetNode->element);
        currentNode = currentNode->next;
        forwardSteps--;
    }

}

// int main()
// {
//     circularListWithReverse<int> x;
//     for(int i = 0; i <2; i++)
//         x.insert(i, i+1);
//     std::cout << x << std::endl;
//     x.reverse();
//     std::cout << x << std::endl;
//     // x.push_back(26);
//     // std::cout << x << std::endl;
//     // x.push_back(26);
//     // x.insert(0, 26);
//     // x.erase(0);
//     x.erase(0);
//     x.erase(0);
//     x.erase(0);
//     std::cout << x << std::endl;
//     std::cout << x.size() << std::endl;
// }