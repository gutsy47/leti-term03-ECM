#ifndef ECM_UTILS_H
#define ECM_UTILS_H

#include <iostream>

std::string getBitsOfSInt(short int);
std::string getBitsOfLDouble(long double);
void swapBitsSInt(short int&, unsigned short, unsigned short);
void swapBitsLDouble(long double&, unsigned short, unsigned short);

#endif //ECM_UTILS_H