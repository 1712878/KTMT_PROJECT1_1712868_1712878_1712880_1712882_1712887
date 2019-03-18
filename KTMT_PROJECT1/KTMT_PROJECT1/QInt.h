#ifndef __QINT_H__
#define __QINT_H__

#include "Bit.h"

class Qint
{
private:
	int size = 4;
	unsigned int data[4];
public:
	Qint();
	// Chuyển một chuỗi Bin -> vào mảng a[4]
	void SetDataBin(string strBin);
	// Chuyển một chuỗi Dec -> vào mảng a[4]
	void SetDataDec(string strDec);
	// In dữ liệu dạng bit trong mảng a[4]
	void PrintQintBit();
	//
	void ScanQint(Qint &x);
	void PrintQInt(Qint x);
};


#endif // !__QINT_H__


