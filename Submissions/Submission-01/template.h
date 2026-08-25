

#ifndef _TEMPLATE_H
#define _TEMPLATE_H

#include <iostream>

template <typename T> void PrintTypeSize(T v) {
    std::cout << "Size: " << sizeof(T) << std::endl;
}

template <typename T> T GetMax(T a, T b) { return a > b ? a : b; }


#endif //_TEMPLATE_H