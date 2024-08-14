#ifndef LEVELORDER_H
#define LEVELORDER_H

#include"../../ch9/case/9-2.cpp"
#include"binaryTreeNode.h"
#include"traversal.h"
#include"../../Tool.h"

template<class T>
void leveOrder(binaryTreeNode<T>* t)//O(n),n為樹的節點個數，若有擴容則O(n + queueSize)
{
    arrayQueue<binaryTreeNode<T>*> container;//O(1),因為其元素是指針類型（帶求證！！！！！！！）
    if(t != nullptr)//O(1)
        container.push(t);//不擴容O(1),擴容O(queueSize)
    else return;//O(1) 如果樹為空，則返回
    while(!container.empty())//O(n), n為樹的節點個數
    {
        cout << container.front()->element << ' ';//O(1)
        if(container.front()->leftChild != nullptr)//O(1)
            container.push(container.front()->leftChild);//O(1)
        if(container.front()->rightChild != nullptr)//O(1)
            container.push(container.front()->rightChild);//O(1)
        // cout << container.front()->leftChild->element << ' ';
        // cout << container.front()->rightChild->element << ' ';
        container.pop();//O(1)
    }
}

/*
//textbook type:

template<class T>
void levelOrder(binaryTreeNode<T>* t)
{
    arrayQueue<binaryTreeNode<T>*> q;
    while(t != nullptr)
    {
        visit(t);
        if(t->leftChild != nullptr)
            q.push(t->leftChild);
        if(t->rightChild != nullptr)
            q.push(t->rightChild);
        try{t = q.front();}
        catch(queueEmpty qe)
        {
            qe.outputMessage();
            return;
        }
        q.pop();
    }
}
*/
#endif // LEVELORDER_H