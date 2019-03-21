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

void PrintIntBit(unsigned int x)
{
	bool a[32];
	int k = 0;
	for (int i = 31; i >= 0; i--)
	{
		bool bit = GetBit(x, i);
		a[k++] = bit;
	}
	for (int i = 0; i < 32; i++)
		cout << a[i];
}