// // #include<iostream>
// // using namespace std;

// // int main()
// // {
// //     int a, b, c;
// //     a = 2, b = 1, c = 0;
// //     cout << a+b*c+b/c;
// // }
// #include"time.h"
// #include<math.h>
// #include"MyTool.h"
// #include<iostream>
// #include<numeric>
// #include<algorithm>
// #include<iterator>
// using namespace std;

// template<class T>
// T sum(T an[], int n)
// {
//     T theSum = 0;
//     // for(int i = 0; i < n; i++)
//     //     theSum += an[i];
//     // return theSum;
//     return accumulate(an, an+5, theSum);
// }

// template<class T>
// T product(T an[], int n)
// {
//     T theProduct = 1;
//     return accumulate(an, an+5, theProduct, multiplies<T>());
// }

// template<class T>
// void permutation(T list[], int k, int m)
// {
//     do
//     {
//     copy(list, list+m+1, ostream_iterator<T>(cout, " "));
//     cout << endl;
//     // for(int i = 0; i < 5; i++)
//     //     cout << list[i] << " ";
//     }while(next_permutation(list, list+m+1));
// }

// int main()
// {
//     // int an[] = {1, 2, 3, 4, 5};
//     // // cout << product<int>(an, 5);
//     // permutation<int>(an, 0, 4);
//     // cout << endl;
//     // // for(int i = 0; i < 5; i++)
//     // //     cout << an[i] << " ";

// //    cout <<  factorial(32);
//     // double n = 10;
//     // for( ;!(pow(2, n)/n < 100); n-= 0.01);
//     // cout << (pow(2, 14)/14  );
//     // cout << n;

//     // clock_t elapsedTime;
//     // clock_t aTime = clock();
//     // cout << aTime << endl << clock()-aTime << endl;
//     // aTime = clock();
//     // cout << aTime << endl << clock()-aTime << endl;
// }

// //1.檢查theIndex是否合法 2.檢查是否有足夠的空間，不夠擴容 3.判斷需要移動的元素所在方向，移動后插入新值 4.更新綫性表的屬性

// // #include"E:\DataStructure\ch5\exercise\31.cpp"
// // template<class T>
// // void circularArrayList<T>::insert(int theIndex, const T &theElement)
// // {
// //     int listSize = size();
// //     if(theIndex < 0 || theIndex > listSize)
// //     {
// //         std::ostringstream s;
// //         s << "theIndex = " << theIndex << " listSize = " << listSize;
// //         throw IllegalParameter(s.str());
// //     }
// //     if(first == -1)
// //     {
// //         element[0] = theElement;
// //         first = last = 0;
// //     }
// //     if(listSize = arrayLength)
// //     {
// //         T* tmp =  new T[2*arrayLength];
// //         //copy elements into new space
// //         int j = 0;
// //         for(int i = first; i != last; i = (i+1)%arrayLength)
// //             tmp[j++] = element[i];
// //         tmp[j] = element[last];
// //         delete []element;
// //         element = tmp;
// //         first = 0;
// //         last = j;
// //         arrayLength*=2;
// //     }
// //     if(theIndex <= (listSize - 1)/2)
// //     {
// //         //移動左邊的元素
// //         // for(int i = first; i < theIndex; i = (i+1)%arrayLength)
// //         //             element[(arrayLength + first + i-1)%arrayLength] = element[i];
// //         // element[theIndex] = theElement;
// //         for(i = 0; i < theIndex; i++)
// //         {
// //             element[(arrayLength+first+i-1)%arrayLength] = element[(i+first)%arrayLength];
// //         }
// //         first = (arrayLength + first - 1)%arrayLength;
// //     }
// //     else
// //     {
// //         // for(int i = last; i > (theIndex + first)%arrayLength; i = (arrayLength + i - 1)%arrayLength)
// //         //     element[(i+1)%arrayLength] = element[i];
// //         for(int i = listSize-1; i >= theIndex; i--)
// //             element[(i+1+first)%arrayLength] = element[(i+first)%arrayLength];
// //         last = (last+1)%arrayLength;
// //     }
// //     element[(theIndex+first)%arrayLength] = theElement;
// // }

// // template<class T>
// // void circularArrayList<T>::earse(int theIndex)
// // {
// //     checkIndex(theIndex);
// //     int listSize = size();
// //     if(listSize == 1)
// //     {
// //         element[first].~T();
// //         first = -1;
// //     }
// //     if(theIndex <= (listSize-1)/2)
// //     {
// //         //shift left side
// //         for(int i = theIndex-1; i >= 0; i--)
// //             element[(i + first+1)%arrayLength] = element[(i+first)%arrayLength];
// //         element[first].~T();
// //        first = (first+1)%arrayLength;
// //     }
// //     else
// //     {
// //         for(int i = theIndex+1; i < listSize; i++)
// //             element[(first+i-1)%arrayLength] = element[(first+i)%arrayLength];
// //         element[last].~T();
// //         last = (arrayLength+last-1)%arrayLength;
// //     }
// // }


// #include"ch5/case/5-12.h"

// int main()
// {
//     try
//     {
//     vectorList<int> x(10);
//     for(int i = 0; i < 5; i++)
//         x.insert(i, i+1);
//     // int i = 0;
//     // x.insert(0, 1);
//     // vectorList<int>::iterator iter = x.end();
//     // std::cout << *(iter);
//     // *iter = 6;
//     // iter = x.begin(); 
//     // while(iter <= x.end())
//     // {
//     //     std::cout << *iter << " ";
//     //     iter++;
//     // }

//     // std::cout << std::endl;
//     x.erase(3);
//     std::cout << x;
//     // int tmp = x.get(0);
//     // x.erase(0);
//     // std::cout << x.indexOf(2);
//     }catch(IllegalParameter ip){ip.outputMessage();}
// }

int main()
{
    int **x;
    x = new int*[4];
    for(int i = 0; i < 4; i++)
        x[i] = new int[3];
    for(int i = 0; i < 4; i++)
        delete []x[i];
    delete []x;
}