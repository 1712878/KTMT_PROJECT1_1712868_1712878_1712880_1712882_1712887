#ifndef __Qfloat_H_
#define __Qfloat_H_
#include"Bit.h"
#include"Process.h"
#include"QInt.h"
#include<string>
class Qfloat
{
private:
	unsigned int BFloat[4];
	int sizeF = 4;
public:
	string BinToDecInt(string bit);
	void SetDataBin(string strBin);
	Qfloat BinToDec(string bit);
	string DecToBin(Qfloat x);
	void  ScanQfloat(Qfloat  &x);
	void PrintQfloat(Qfloat x);
	Qfloat();
	~Qfloat();
};
#endif


