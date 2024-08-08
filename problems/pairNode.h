#ifndef PAIRNODE_H
#define PAIRNODE_H

template<class K, class E>
struct pairNode
{
    typedef pair<const K, E> pairType;
    pairNode(pairType& thePair):element(thePair), next(nullptr){}
    pairNode(pairType& thePair, pairNode<K, E>* theNext):element(thePair), next(theNext){}
    //data
    pairType element;
    //pointer
    pairNode<K, E>*  next;
};

#endif //PARINODE_H