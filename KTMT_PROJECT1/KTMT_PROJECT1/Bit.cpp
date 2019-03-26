#include "Bit.h"

bool GetBit(unsigned int x, int pos)
{
	return (x >> pos) & 1;
}

unsigned int SetBitOne(unsigned int & x, int pos)
{
	x = (1 << pos) | x;
	return x;
}

unsigned int SetBitZero(unsigned int & x, int pos)
{
	x = (~(1 << pos))&x;
	return x;
}

unsigned int FlipBit(unsigned int &x, int pos)
{
	x = (1 << pos) ^ x;
	return x;
}

