#ifndef PAIRNODE_H
#define PAIRNODE_H

using namespace std;

template<class K, class E>
struct pairNode
{
    typedef pair<const K, E> pairType;
    pairType element;
    pairNode<K, E>* next;

    pairNode(const pairType& thePair):element(thePair){next = nullptr;}
    pairNode(const pairType& thePair, pairNode<K, E>* theNext):element(thePair){next = theNext;}
};

#endif // PAIRNODE_H