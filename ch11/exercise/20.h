//對一顆使用數組描述的二叉樹編寫前序遍歷程序
//假設這顆樹的根用1號位置存儲
#ifndef ARRAYTREEPREORDER_H
#define ARRAYTREEPREORDER_H

#include<iostream>
using namespace std;

template<class T>
void visit(pair<bool, T>* tree, int count)
{//打印element
    cout << tree[count].second << ' ';
}

//MLR
template<class T>
void preOrder(pair<bool, T>* theTree, int count, int numOfNode)//O(numberOfNode)
{//使用前序遍历，遍历数组树
    if(count > numOfNode) return;
    visit(theTree, count);
    preOrder(theTree, count*2, numOfNode);
    preOrder(theTree, count*2 + 1, numOfNode);
}

#endif // ARRAYTREEPREORDER_H