#include"../case/extendedChain.cpp"

template<class T>
void extendedChain<T>::circularShift(int theSteps)
{
    if(!firstNode) return;
    chainNode<T>* currentNode = firstNode;
    for(int i = 0; i < theSteps; i++)
    {
        chainNode<T>* nextNode = currentNode->next;
        push_back(currentNode->element);
        delete currentNode;
        currentNode = nextNode;
    }
    firstNode = currentNode;
}

int main()
{
    extendedChain<int> x;
    for(int i = 0; i < 5; i++)
    {
        x.insert(i, i);
    }
    cout << x << endl;
    x.circularShift(0);
    cout << x << endl;
}