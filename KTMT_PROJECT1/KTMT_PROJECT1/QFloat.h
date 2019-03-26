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
	// Khởi tạo số thực QFloat = 0.0
	QFloat();
	string GetDataBin();
	void SetDataBin(string str);
	string BinToDec(string str);
	string DecToBin(string str);
	void ScanQFloat();
	void PrintQFloat();
};
#endif


