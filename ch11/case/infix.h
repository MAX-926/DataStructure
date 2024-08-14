//輸出完全括號化的中綴表達式
#ifndef INFIX_H
#define INFIX_H

#include"binaryTreeNode.h"

template<class T>
void visit(binaryTreeNode<T>* t)
{
    cout << t->element << ' ';
}

template<class T>
void infix(binaryTreeNode<T>* t)
{//以中序遍歷輸出，帶括號
    if(t != nullptr)
    {//LMR 這樣做會把一顆完整的子樹用（）包括起來（逐層）
        cout << '(';
        infix(t->leftChild);//左操作數
        visit(t);//操作符
        infix(t->rightChild);//右操作數
        cout << ')';
    }
}
#endif // INFIX_H