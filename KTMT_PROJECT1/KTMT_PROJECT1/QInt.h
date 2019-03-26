#ifndef __QINT_H__
#define __QINT_H__

#include "Bit.h"

class QInt
{
private:
	int size = 4;
	unsigned int data[4];
public:
	// Khởi tạo số QInt = 0
	QInt();
	// Chuyển một chuỗi Bin -> vào mảng a[4]
	void SetDataBin(string str);
	// Chuyển một chuỗi Dec -> vào mảng a[4]
	void SetDataDec(string str);
	// Chuyển một chuỗi Hex -> vào mảng a[4]
	void SetDataHex(string str);

	// Lấy data dạng Bin đầy đủ
	string GetDataBin();
	// Lấy data dạng Bin
	string GetDataBit();
	// Lấy data dạng Dec
	string GetDataDec();
	// Lấy data dạng Hex
	string GetDataHex();

	// Nhập số QInt dạng thập phân
	void ScanQInt();
	// In QInt dạng thập phân
	void PrintQInt();
	// In dữ liệu dạng Bin
	void PrintQIntBin();
	// In dữ liệu dạng Hex
	void PrintQIntHex();

	string DecToBin(string str);
	string BinToDec(string bit);
	string BinToHex(string bit);
	string DecToHex(string str);
	string HexToBin(string str);
	string HexToDec(string str);

	friend QInt operator + (QInt a, QInt b);
	QInt TwoComplementQInt();
	friend QInt operator - (QInt a, QInt b);
	friend QInt operator * (QInt a, QInt b);
	friend QInt operator / (QInt a, QInt b);

	bool operator < (QInt obj);
	bool operator > (QInt obj);
	bool operator == (QInt obj);
	bool operator <= (QInt obj);
	bool operator >= (QInt obj);
	QInt operator = (QInt obj);

	friend QInt& operator & (QInt obj, QInt Kobj);
	friend QInt& operator | (QInt obj, QInt Kobj);
	friend QInt& operator ^ (QInt obj, QInt Kobj);
	friend QInt &operator ~ (QInt obj);

	friend QInt operator << (QInt obj, int NumOfBitMove);
	friend QInt operator >> (QInt obj, int NumOfBitMove);
	QInt rol(int NumOfBitMove);
	QInt ror(int NumOfBitMove);
};


#endif // !__QINT_H__


