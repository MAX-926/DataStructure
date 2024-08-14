#include"22.h"

template<class T>
pair<bool, T>* tree;

int numberOfNode = 15;

int main()
{
    tree<char> = new pair<bool, char>[numberOfNode + 1];
    for(int i = 0; i < numberOfNode + 1; i++)
        tree<char>[numberOfNode].first = false;
    
    tree<char>[1].first = true; tree<char>[1].second = '/';
    tree<char>[2].first = true; tree<char>[2].second = '+';
    tree<char>[3].first = true; tree<char>[3].second = '*';
    tree<char>[4].first = true; tree<char>[4].second = '-';
    tree<char>[5].first = true; tree<char>[5].second = '+';
    tree<char>[6].first = true; tree<char>[6].second = '+';
    tree<char>[7].first = true; tree<char>[7].second = '*';
    tree<char>[9].first = true; tree<char>[9].second = 'a';
    tree<char>[10].first = true; tree<char>[10].second = 'x';
    tree<char>[11].first = true; tree<char>[11].second = 'y';
    tree<char>[13].first = true; tree<char>[13].second = 'b';
    tree<char>[14].first = true; tree<char>[14].second = 'c';
    tree<char>[15].first = true; tree<char>[15].second = 'a';

    postOrder<char>(tree<char>, 1, numberOfNode);
}