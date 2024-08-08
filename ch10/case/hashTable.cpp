// test hash table class
#include <iostream>
#include "hashTable.h"

using namespace std;

// int main()
// {
//    hashTable<int, int> z(11);
//    pair<int, int> p;

//    // test insert
//    p.first = 2; p.second = 10;
//    z.insert(p);
//    p.first = 10; p.second = 50;
//    z.insert(p);
//    p.first = 24; p.second = 120;
//    z.insert(p);
//    p.first = 32; p.second = 160;
//    z.insert(p);
//    p.first = 3; p.second = 15;
//    z.insert(p);
//    p.first = 12; p.second = 60;
//    z.insert(p);
//    cout << "The dictionary is " << endl << z << endl;
//    cout << "Its size is " << z.size() << endl;

//    // test find
//    cout << "Element associated with 2 is " << z.find(2)->second << endl;
//    cout << "Element associated with 10 is " << z.find(10)->second << endl;
//    cout << "Element associated with 12 is " << z.find(12)->second << endl;

// }

int main()
{
   hashTable<int, int> z;
   pair<int, int> p;

   // test insert
   p.first = 2; p.second = 10;
   z.insert(p);
   p.first = 10; p.second = 50;
   z.insert(p);
   p.first = 6; p.second = 30;
   z.insert(p);
   p.first = 8; p.second = 40;
   z.insert(p);
   p.first = 1; p.second = 5;
   z.insert(p);
   p.first = 12; p.second = 60;
   z.insert(p);

   p.first = 24; p.second = 160;
   z.insert(p);
   p.first = 35; p.second = 230;
   z.insert(p);
   p.first = 19; p.second = 65;
   z.insert(p);
   p.first = 15; p.second = 69;
   z.insert(p);
   p.first = 40; p.second = 80;
   z.insert(p);

   cout << "The chain is " << z << endl;
   cout << "Its size is " << z.size() << endl;

   // test find
   cout << "Element associated with 1 is " << z.find(1)->second << endl;
   cout << "Element associated with 6 is " << z.find(6)->second << endl;
   cout << "Element associated with 12 is " << z.find(12)->second << endl;

   // test erase
   z.erase(1);
   z.erase(2);
   z.erase(6);
   z.erase(12);
   cout << "Deleted 1, 2, 6, 12" << endl;
   cout << "The chain is " << z << endl;
   cout << "Its size is " << z.size() << endl;

   
   cout << "Element associated with 40 is " << z.find(40)->second << endl;
   cout << "Element associated with 24 is " << z.find(24)->second << endl;
   cout << "Element associated with 35 is " << z.find(35)->second << endl;

   cout << "Element associated with 15 is " << z.find(15)->second << endl;
   cout << "Element associated with 8 is " << z.find(8)->second << endl;
   cout << "Element associated with 19 is " << z.find(19)->second << endl;
   cout << "Element associated with 10 is " << z.find(10)->second << endl;

}
