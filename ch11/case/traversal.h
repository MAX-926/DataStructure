#ifndef TRAVERSAL_H
#define TRAVERSAL_H
//前序遍歷二叉樹
//中左右
#include"../case/binaryTreeNode.h"

template<class T>
void visit(binaryTreeNode<T>* t)
{//訪問節點t，僅輸出element域
    cout << t->element << " ";
}

template<class T>
void preOrder(binaryTreeNode<T>* t)
{
    if(t != nullptr)
    {
        visit(t);
        preOrder(t->leftChild);
        preOrder(t->rightChild);
    }
}

template<class T>
void inOrder(binaryTreeNode<T>* t)
{
    if(t != nullptr)
    {
        inOrder(t->leftChild);
        visit(t);
        inOrder(t->rightChild);
    }
}

template<class T>
void postOrder(binaryTreeNode<T>* t)
{
    if(t != nullptr)
    {
        postOrder(t->leftChild);
        postOrder(t->rightChild);
        visit(t);
    }
}
#endif // TRAVERSAL_H