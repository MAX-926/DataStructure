#include"../case/6-2.h"

template<class T>
void chain<T>::split(chain<T> &a, chain<T> &b)
{
    if(!this->listSize)
    {
        return;
    }
   if(a.firstNode)
   {
    chainNode<T>* nextNode = a.firstNode->next;
    delete a.firstNode;
    a.firstNode = nextNode;
   }
   if(b.firstNode)
   {
    chainNode<T>* nextNode = b.firstNode->next;
    delete b.firstNode;
    b.firstNode = nextNode;
   }
    // a.firstNode = NULL;
    // b.firstNode = NULL;
    a.listSize = 0;
    b.listSize = 0;
   int theIndex = 0;
    chainNode<T> *ap = a.firstNode, *bp = b.firstNode;
    while(this->firstNode != NULL)
    {
        if(theIndex % 2 == 0)
        {
            if(b.firstNode == NULL)
            {
                b.firstNode = this->firstNode;
                this->firstNode = this->firstNode->next;
                bp = b.firstNode;
                b.listSize++;
                theIndex++;
                // continue;
            }
            else
            {
                bp->next = this->firstNode;
                bp = bp->next;
                this->firstNode = this->firstNode->next;
                b.listSize++;
                theIndex++;
                // continue;
            }
        }
        else if(theIndex % 2 != 0)
        {
            if(a.firstNode == NULL)
            {
                a.firstNode = this->firstNode;
                this->firstNode = this->firstNode->next;
                ap = a.firstNode;
                a.listSize++;
                theIndex++;
                // continue;
            }
            else
            {
                ap->next = this->firstNode;
                ap = ap->next;
                this->firstNode = this->firstNode->next;
                a.listSize++;
                // ap->next
                theIndex++;
                // continue;
            }
            // if(this->firstNode->next == NULL && theIndex == 0){b.firstNode = NULL;}
        }
    }
    if(theIndex == 1){a.firstNode = NULL;}
    else ap->next = NULL;
    bp->next = NULL;
}

int main()
{
    chain<int> a, b, c;
    for(int i = 0; i < 1; i++)
    {
        c.insert(i, i);
    }
    cout << "c:" << c << endl;
    c.split(a, b);
    cout << "a:" << a << endl;
    cout << "b:" << b << endl;
    cout << "c:" << c << endl;
}