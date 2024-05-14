#ifndef ch5_5_2_H
#define ch5_5_2_H
#include"../../MyTool.h"
#include<algorithm>

template<class T>
void changeLength1D(T* &a, int oldLength, int newLength)
{
    //异常检测与处理
    if(newLength < 0) throw IllegalParameter("new length must be >= 0");
    T* tmp = new T[newLength];
    //M1:
    // for(int i = 0; i < oldLength; i++)
    //     tmp[i] = a[i];
    //M2:
    // int number = min(newLength, oldLength);
    // std::copy(a, a+oldLength, tmp);
    std::copy(a, a+(newLength > oldLength? oldLength:newLength), tmp);
    delete []a;
    a = tmp;
}

#endif //ch5_5_2_H
// int main()
// {
//     //
//     int *ap, *bp;
//     create1DArray<int>(ap, 5);
//     // create1DArray<int>(bp, 5);
//     init1DArray<int>(ap, 5, 26);
//     // init1DArray<int>(bp, 5, 1);
//     try
//     {
//     changeLength1D<int>(ap, 5, -1);
//     }catch(IllegalParameter ip)
//     {
//         ip.outputMessage();
//     }
//     // ap[1000] = 100;
//     // std::cout << ap[1000];
//     print_1D_array_incpp<int>(ap, 10);
//     // print_1D_array_incpp<int>(bp, 5);
// }