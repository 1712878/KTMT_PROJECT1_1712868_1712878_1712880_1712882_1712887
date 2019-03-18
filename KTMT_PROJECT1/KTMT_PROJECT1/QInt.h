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
	bool * DecToBin(QInt x);
	QInt BinToDec(bool *bit);
	char *BinToHex(bool *bit);
	char *DecToHex(QInt x);

	QInt operator + (const QInt& obj);
	QInt operator - (const QInt& obj);
	QInt operator * (const QInt& obj);
	QInt operator / (const QInt& obj);

	bool operator < (const QInt& obj);
	bool operator > (const QInt& obj);
	bool operator == (const QInt& obj);
	bool operator <= (const QInt& obj);
	bool operator >= (const QInt& obj);
	bool operator = (const QInt& obj);

	bool operator & (const QInt& obj);
	bool operator | (const QInt& obj);
	bool operator ^ (const QInt& obj);
	//bool operator ~ (const QInt& obj);

	QInt operator << (const QInt& obj);
	QInt operator >> (const QInt& obj);
	//QInt operator rol (const QInt& obj);
	//QInt operator ror (const QInt& obj);
};


#endif // !__QINT_H__


