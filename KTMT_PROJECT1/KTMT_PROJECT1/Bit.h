#ifndef __BIT_H__
#define __BIT_H__

#include <iostream>
#include <string>
using namespace std;
// Lấy bit tại vị trị pos từ phải qua
bool GetBit(unsigned int x, int pos);
// Bật bit lên 1 tại pos từ phải qua
unsigned int SetBitOne(unsigned int &x, int pos);
// Tắt bit xuống 0 tại pos từ phải qua
unsigned int SetBitZero(unsigned int &x, int pos);
// Đảo bit 0 <-> 1 tại pos từ phải qua
unsigned int FlipBit(unsigned int &x, int pos);



#endif // !__BIT_H__
