#ifndef __BIT_H__
#define __BIT_H__

#include <iostream>
#include <string>
using namespace std;

bool GetBit(unsigned int x, int pos);
unsigned int SetBitOne(unsigned int &x, int pos);
unsigned int SetBitZero(unsigned int &x, int pos);
void PrintIntBit(unsigned int x);


#endif // !__BIT_H__
