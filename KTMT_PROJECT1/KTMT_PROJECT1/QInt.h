#ifndef __QINT_H__
#define __QINT_H__

#include "Bit.h"

class QInt
{
private:
	int size = 4;
	unsigned int data[4];
public:
	QInt();
	// Chuyển một chuỗi Bin -> vào mảng a[4]
	void SetDataBin(string strBin);
	// Chuyển một chuỗi Dec -> vào mảng a[4]
	void SetDataDec(string strDec);
	// In dữ liệu dạng bit trong mảng a[4]
	void PrintQIntBit();
	//Lấy Bit từ data
	string GetDataBin();

	void ScanQInt(QInt &x);
	void PrintQInt(QInt x);
};


#endif // !__QINT_H__


