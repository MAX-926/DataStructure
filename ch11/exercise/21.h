//使用中序遍历处理数组树
//對一顆使用數組描述的二叉樹編寫中序遍歷程序
//假設這顆樹的根用1號位置存儲
#ifndef ARRAYTREEINORDER_H
#define ARRAYTREEINORDER_H

#include<iostream>
using namespace std;

template<class T>
void visit(pair<bool, T>* tree, int count)
{//打印element
    cout << tree[count].second << ' ';
}

//LMR
template<class T>
void inOrder(pair<bool, T>* theTree, int count, int numOfNode)//O(numberOfNode)
{//使用中序遍历，遍历数组树
    if(count > numOfNode) return;
    inOrder(theTree, count*2, numOfNode);
    visit(theTree, count);
    inOrder(theTree, count*2 + 1, numOfNode);
}

#endif // ARRAYTREEINORDER_H