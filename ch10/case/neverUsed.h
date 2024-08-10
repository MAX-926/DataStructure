#include"../case/dictionary.h"

template<class K, class E>
class hashTable:public dictionary<K, E>
{
    public:
        hashTable(int theDivisor = 11)
        {
            divisor = theDivisor;
            dSize = 0;
            table = new pair<const K, E>*[divisor];
            neverUsed = new bool[divisor];
            for(int i = 0; i < divisor; i++)
            {
                table[i] = nullptr;
                neverUsed[i] = true;
            }
        }
        ~hashTable() { delete[] table; }
        bool empty()const {return dSize == 0;}
        int size()const {return dSize;}
        pair<const K, E>* find(const K&)const;
        void insert(const pair<const K, E>&);
        void erase(const K&);
    protected:
        int search(const K&)const;
        pair<const K, E>** table;
        int dSize;
        int divisor;
        hash<K> hash;
        bool* neverUsed;
};

template<class K, class E>
int hashTable<K, E>::search(const K& theKey)const
{
    int b = hash(theKey) % divisor;
    int j = b;
    do
    {
        if(table[j] == nullptr && neverUsed[j] == false)
        {
            j = (j + 1) % divisor;
            continue;
        }
        if(neverUsed[j] == true || (table[j] != nullptr && table[j]->first == theKey)
            return j;
        j = (j + 1) % divisor;
    }while(j != b);
    return j;
}

template<class K, class E>
pair<const K, E>* hashTable<K, E>::find(const K& theKey)const
{

}