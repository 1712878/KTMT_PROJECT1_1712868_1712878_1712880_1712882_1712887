#ifndef __QFloat_H_
#define __QFloat_H_
#include"Bit.h"
#include"Process.h"
#include"QInt.h"
#include<string>
class QFloat
{
private:
	unsigned int BFloat[4];
	int sizeF = 4;
public:
	QFloat();
	string BinToDecInt(string bit);
	string GetDataBin();
	void SetDataBin(string strBin);
	string BinToDec(string bit);
	string DecToBin(string x);
	void ScanQFloat();
	void PrintQFloat();
};
#endif


