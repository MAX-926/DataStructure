#include"../../MyTool.h"
#include"../case/6-2.h"
#include<time.h>
#include<string.h>
//bubleSort
template<class T>
void chain<T>::bubleSort()//O(listSize^2)
{
    if(listSize == 1 || listSize == 0) return;
    chainNode<T>* currentNode = firstNode;
    int innerLoopTimes = listSize-1;
    for(int n = 0; n < listSize-1; n++)
    {
        for(int i = 1; i < innerLoopTimes; i++)
        {
            if(currentNode->element > currentNode->next->element)
                swap(currentNode->element, currentNode->next->element);
            currentNode = currentNode->next;
        }
        --innerLoopTimes;
        currentNode = firstNode;
    }
}

//selectSort
template<class T>
void chain<T>::selectSort()
{
    //选择修改firstNode为最小
    chainNode<T>* nodeOnProcess = firstNode;
    T minElement = firstNode->element;
    while(nodeOnProcess->next != NULL)
    {
        chainNode<T>* currentNode = nodeOnProcess->next;
        chainNode<T>* minNodeAddress = nodeOnProcess;
        while(currentNode != NULL)
        {
            if(currentNode->element < nodeOnProcess->element)
            {
                minNodeAddress = currentNode;
            }
            currentNode = currentNode->next;
        }
        swap(minNodeAddress->element, nodeOnProcess->element);
        nodeOnProcess = nodeOnProcess->next;
    }
}

//rankSort
template<class T>
void chain<T>::rankSort()//量级在O(listSize^2)
{
    if(listSize == 1 || listSize == 0) return;
    //开辟rank数组存放空间
    int* rankA = new int[listSize];//O(listSize) if T is user-built type, O(1) if T is built-in type
    //对rank数组进行“0”初始化
    memset(rankA, 0, sizeof(int)*listSize);//O(1) or O(listSize)?
    //初始化比较节点
    chainNode<T>* compareNode = firstNode;
    //设定比较节点的索引值
    int indexOfCompareNode = 0;
    //最大索引值
    // const int maxIndex = listSize-1;
    while(compareNode->next != NULL)//O(listSize^2)
    {
        int iterIndex = indexOfCompareNode + 1;
        chainNode<T>* iter = compareNode->next;
        while(iter != NULL)
        {
            if(iter->element >= compareNode->element)
            {
                rankA[iterIndex++]++;
                iter = iter->next;
            }
            else
            {
                rankA[indexOfCompareNode]++;
                iter = iter->next;
                iterIndex++;
            }
        }
        compareNode = compareNode->next;
        indexOfCompareNode++;
    }
    // print_1D_array_incpp(rankA, listSize);
    //根据rankA对chain进行重排
    compareNode = firstNode;
    int compareNodeIndex = 0;
    while(compareNode->next != NULL)// 复杂度不会超过listSize^2
    {
        while(rankA[compareNodeIndex] != compareNodeIndex)
        {
            chainNode<T>* swapNode = firstNode;
            int swapNodeIndex = 0;
            for(int i = 0; i < rankA[compareNodeIndex]; i++)
            {
                swapNode = swapNode->next;
                swapNodeIndex++;
            }
            swap(compareNode->element, swapNode->element);
            swap(rankA[compareNodeIndex], rankA[swapNodeIndex]);
        }
        compareNode = compareNode->next;
        compareNodeIndex++;
    }
}

int main()
{
    chain<float> x;
    int max = 10;
    for(int i = 0; i < 2; i++)
        x.insert(i, max--);
    cout << x << endl;
    // x.bubleSort();
    // x.selectSort();
    x.rankSort();
    cout << x << endl;
}