#ifndef BINARYTREENODE_H
#define BINARYTREENODE_H

using namespace std;

template<class T>
struct binaryTreeNode
{
    //data
    T element;
    //pointer
    binaryTreeNode<T>* leftChild;//left subtree
    binaryTreeNode<T>* rightChild;//right subtree
    //constructor
    binaryTreeNode() { leftChild = rightChild = nullptr; }
    binaryTreeNode(const T& theElement):element(theElement) { leftChild = rightChild = nullptr; }
    binaryTreeNode(const T& theElement, 
                         binaryTreeNode<T>* theLeftChild, 
                         binaryTreeNode<T>* theRightChild)
                         :element(theElement)
    {
        leftChild = theLeftChild;
        rightChild = theRightChild;
    }
};

#endif //BINARYTREENODE_H