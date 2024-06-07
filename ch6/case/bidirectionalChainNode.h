#ifndef BIDIRECTIONALCHAINNODE_H
#define BIDIRECTIONALCHAINNODE_H

// template<class T>
// struct bidirectionalChainNode
// {
//     bidirectionalChainNode(const T& theElement = 0, 
//                            bidirectionalChainNode<T>* theNext = NULL, 
//                            bidirectionalChainNode<T>* thePrevious = NULL)
//                            {
//                                next = theNext;
//                                previous = thePrevious;
//                            }
//     // ~bidirectionalChainNode(){}
//     //Data:
//     T element;
//     //Pointer:
//     bidirectionalChainNode<T>* next;
//     bidirectionalChainNode<T>* previous;
// };

template<class T>
struct bdChainNode
{
    bdChainNode(const T& theElement = 0, 
                           bdChainNode<T>* theNext = NULL, 
                           bdChainNode<T>* thePrevious = NULL)
                           {
                               element = theElement;
                               next = theNext;
                               previous = thePrevious;
                           }
    // ~bidirectionalChainNode(){}
    //Data:
    T element;
    //Pointer:
    bdChainNode<T>* next;
    bdChainNode<T>* previous;
};


#endif //BIDIRECTIONALCHAINNODE_H