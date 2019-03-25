#include "QInt.h"
#include "Process.h"

// Khởi tạo mặc định không tham số QInt
QInt::QInt()
{
	for (int i = 0; i < this->size; i++)
		this->data[i] = 0;
}
// Lưu giá trị chuỗi Bin vào QInt
void QInt::SetDataBin(string strBin)
{
	for (int i = 0; i < this->size; i++)
		this->data[i] = 0;
	int len = strBin.length();
	for (int i = 0; i < 128; i++)
	{
		len--;
		if (len >= 0 && strBin[len] == '1')
			SetBitOne(this->data[this->size - 1 - i / 32], i % 32);
	}
}
// Lưu giá trị chuỗi Dec vào QInt
void QInt::SetDataDec(string strDec)
{
	string bin = this->DecToBin(strDec);
	this->SetDataBin(bin);
}
// Lưu giá trị chuỗi Hexa vào QInt
void QInt::SetDataHex(string strHex)
{
	string bin = this->HexToBin(strHex);
	this->SetDataBin(bin);
}

// Lấy giá trị QInt dạng Bin
string QInt::GetDataBin()
{
	string result;
	result.resize(128);
	for (int i = 0; i < 128; i++)
		result[i] = (GetBit(this->data[i / 32], 31 - i % 32) + '0');
	return result;
}

string QInt::GetDataDec()
{
	QInt flag;
	string str = this->GetDataBin();
	string des = flag.BinToDec(str);
	return des;
}

string QInt::GetDataHex()
{
	QInt flag;
	string str = this->GetDataBin();
	string des = flag.BinToHex(str);
	return des;
}

// Nhập số QInt dạng thập phân
void QInt::ScanQInt()
{
	string str;
	cout << "Moi Ban Nhap So Vao: ";
	getline(cin >> ws, str);
	this->SetDataDec(str);
}
// In QInt dạng thập phân
void QInt::PrintQInt()
{
	string temp = this->GetDataBin();
	cout << this->BinToDec(temp);
}
// In QInt dạng Bin
void QInt::PrintQIntBin()
{
	string temp = this->GetDataBin();
	int pos = temp.find_first_not_of('0');
	temp.erase(0, pos);
	cout << temp;
}
// In QInt dạng Hex
void QInt::PrintQIntHex()
{
	string temp = this->BinToHex(this->GetDataBin());
	int pos= pos = temp.find_first_not_of('0');
	temp.erase(0, pos);
	cout << temp;
}

string QInt::DecToBin(string str)
{
	string result;
	bool minus = false;
	if (str[0] == '-')
	{
		minus = true;
		str.erase(str.begin());
	}
	result = ConvertBigIntToBin(str,128);
	if (minus)
		TwoComplement(result,128);
	return result;
}
string QInt::BinToDec(string bit)
{
	AddBitZero(bit,128);
	string result = "";
	bool minus = false;
	if (bit[0] == '1')
	{
		minus = true;
		TwoComplement(bit,128);
	}
	bit.erase(bit.begin());
	int len = bit.length();
	for (int i = len - 1; i >= 0; i--)
	{
		if(bit[i] == '1')
			result = AddTwoIntString(result, PositivePowTwo(len - i - 1));
	}
	if (minus)
		result.insert(0, 1, '-');
	return result;
}
string QInt::BinToHex(string bit)
{
	AddBitZero(bit,128);
	string result = "";
	int len = bit.length();
	string temp;
	while (len > 0)
	{
		temp.append(bit,len - 4, 4);
		result.insert(0, 1, ConvertBinToHex(temp));
		len -= 4;
		temp = "";
		bit.resize(len);
	}
	return result;
}
string QInt::DecToHex(string str)
{
	string result;
	result = this->DecToBin(str);
	result = this->BinToHex(result);
	return result;
}
string QInt::HexToBin(string str)
{
	string result;
	int len = str.length();
	for (int i = len-1; i >= 0; i--)
		result.insert(0, ConvertHexToBin(str[i]));
	return result;
}
string QInt::HexToDec(string str)
{
	string result;
	result = this->HexToBin(str);
	result = this->BinToDec(result);
	return result;
}

QInt operator+(QInt a, QInt b)
{
	int rem = 0, i = 127;  // phàn tử nằm ở cuối mảng 0 -> 127
	int n = 32;					//  Số bit mà kiểu int lưu trữ
	QInt result;
	while (i >= 0)
	{
		rem += GetBit(a.data[i / n], n - i % n - 1) + GetBit(b.data[i / n], n - i % n - 1);
		if (rem % 2 == 1)
			SetBitOne(result.data[i / n], n - i % n - 1);

		rem /= 2;       //  Lấy bit nhớ
		i--;
	}
	return QInt(result);
}

QInt QInt::TwoComplementQInt()
{
	int n = 32;
	QInt tmp;
	for (int i = 127; i >= 0; i--)
	{
		FlipBit(this->data[i / n], n - i % n - 1);
	}
	SetBitOne(tmp.data[3], 0);
	*this = *this + tmp;
	return QInt(*this);
}
QInt operator-(QInt a, QInt b)
{
	QInt result;
	b.TwoComplementQInt();
	result = a + b;
	return QInt(result);
}

QInt operator*(QInt a, QInt b)
{
	QInt tmp, result;
	int n = 32;
	for (int i = 127; i >= 0; i--)
	{
		if (GetBit(b.data[i / 32], n - i % n - 1) == 1)
		{
			tmp = a << (127 - i);
			result = result + tmp;
		}
	}
	return QInt(result);
}

QInt operator/(QInt a, QInt b)
{
	QInt A, Q = a, M = b, tmp;
	int k = 128, storeBit, sign = 0, signNumQ, signNumM;
	//  Xét dấu đầu vào 
	signNumQ = GetBit(Q.data[0], 31);
	signNumM = GetBit(M.data[0], 31);
	// Lấy bit đầu để kiểm tra dấu => lấy abs() & dấu của thương
	if (signNumQ == 1 && signNumM == 0)
	{

		Q.TwoComplementQInt();
		sign = 1;
	}
	else if (signNumQ == 0 && signNumM == 1)
	{

		M.TwoComplementQInt();
		sign = 1;
	}
	else if (signNumQ == 1 && signNumM == 1)
	{
		Q.TwoComplementQInt();
		M.TwoComplementQInt();
		sign = 0;
	}
	else
		sign = 0;
	

	if (Q < tmp)
	{
		for (int i = k - 1; i >= 0; i--)
			SetBitOne(A.data[i / 32], 32 - i % 32 - 1);
	}
	
	while (k > 0)
	{
		A = A << 1;
		storeBit = GetBit(Q.data[0], 31);
		if (storeBit == 1)
			SetBitOne(A.data[3], 0);
		else
			SetBitZero(A.data[3], 0);
		Q = Q << 1;

		A = A - M;
		if (A < tmp )
		{
			SetBitZero(Q.data[3], 0);
			A = A + M;
		}
		else
			SetBitOne(Q.data[3], 0);

		k = k - 1;
	}
	// Đổi dấu của thương đk sign = 1
	if (sign == 1)
		Q.TwoComplementQInt();

	return QInt(Q);
}

bool QInt::operator<(QInt obj)
{
	int len = 127;
	int ThisD = GetBit(this->data[0], 31);
	int ObjD = GetBit(obj.data[0], 31);
	if (ThisD < ObjD)
		return false;
	if (ThisD > ObjD)
		return true;
	for (int i = 1; i < 128; i++)
	{
		int GetThis = GetBit(this->data[i / 32], (len - i) % 32);
		int GetObj = GetBit(obj.data[i / 32], (len - i) % 32);
		if (GetThis > GetObj)
			return false;
		if (GetThis < GetObj)
			return true;
	}
	return false;
}

bool QInt::operator>(QInt  obj)
{
	int len = 127;
	int ThisD = GetBit(this->data[0], 31);
	int ObjD = GetBit(obj.data[0], 31);
	if (ThisD > ObjD)
		return false;
	if (ThisD < ObjD)
		return true;
	for (int i = 1; i < 128; i++)
	{
		int GetThis = GetBit(this->data[i / 32], (len - i) % 32);
		int GetObj = GetBit(obj.data[i / 32], (len - i) % 32);
		if (GetThis < GetObj)
			return false;
		if (GetThis > GetObj)
			return true;
	}
	return false;
}

bool QInt::operator==(QInt obj)
{
	for (int i = 0; i < 128; i++)
	{
		int GetThis = GetBit(this->data[i / 32], i % 32);
		int GetObj = GetBit(obj.data[i / 32], i % 32);
		if (GetThis != GetObj)
			return false;
	}
	return true;
}

bool QInt::operator<=(QInt obj)
{
	int len = 127;
	int ThisD = GetBit(this->data[0], 31);
	int ObjD = GetBit(obj.data[0], 31);
	if (ThisD < ObjD)
		return false;
	if (ThisD > ObjD)
		return true;
	for (int i = 1; i < 128; i++)
	{
		int GetThis = GetBit(this->data[i / 32], (len - i) % 32);
		int GetObj = GetBit(obj.data[i / 32], (len - i) % 32);
		if (GetThis > GetObj)
			return false;
		if (GetThis < GetObj)
			return true;
	}
	return true;
}

bool QInt::operator>=(QInt obj)
{
	int len = 127;
	int ThisD = GetBit(this->data[0], 31);
	int ObjD = GetBit(obj.data[0], 31);
	if (ThisD > ObjD)
		return false;
	if (ThisD < ObjD)
		return true;
	for (int i = 1; i < 128; i++)
	{
		int GetThis = GetBit(this->data[i / 32], (len - i) % 32);
		int GetObj = GetBit(obj.data[i / 32], (len - i) % 32);
		if (GetThis < GetObj)
			return false;
		if (GetThis > GetObj)
			return true;
	}
	return true;
}

QInt QInt::operator=(QInt obj)
{
	string a;
	string temp = obj.GetDataBin();
	this->SetDataBin(temp);
	return*this;
}

QInt & operator&(QInt obj, QInt Kobj)
{
	QInt temp;
	string result;
	result.resize(128);
	string a = obj.GetDataBin();
	string b = Kobj.GetDataBin();
	for (int i = 0; i < 127; i++)
	{
		if (a[i] == '1'&&b[i] == '1')
		{
			result[i] = '1';
		}
		else result[i] = '0';
	}
	temp.SetDataBin(result);
	return temp;
}

QInt & operator|(QInt obj, QInt Kobj)
{
	QInt temp;
	string result;
	result.resize(128);
	string a = obj.GetDataBin();
	string b = Kobj.GetDataBin();
	for (int i = 0; i < 127; i++)
	{
		if (a[i] == '0'&&b[i] == '0')
		{
			result[i] = '0';
		}
		else result[i] = '1';
	}
	temp.SetDataBin(result);
	return temp;
}

QInt & operator^(QInt obj, QInt Kobj)
{
	QInt temp;
	string result;
	result.resize(128);
	string a = obj.GetDataBin();
	string b = Kobj.GetDataBin();
	for (int i = 0; i < 127; i++)
	{
		if (a[i] == b[i])
		{
			result[i] = '0';
		}
		else result[i] = '1';
	}
	temp.SetDataBin(result);
	return temp;
}

QInt & operator~(QInt obj)
{

	QInt temp;
	string result;
	result.resize(128);
	string a = obj.GetDataBin();
	for (int i = 0; i < 127; i++)
	{
		if (a[i] == '1')
		{
			result[i] = '0';
		}
		else result[i] = '1';
	}
	temp.SetDataBin(result);
	return temp;
}

//Dịch trái
QInt operator<<(QInt obj,int SoBitDich)
{
	QInt des;
	string str;
	str = obj.GetDataBin();
	for (int i = 0; i < str.size() - SoBitDich; i++)
	{
		str.at(i) = str.at(i + SoBitDich);
	}
	for (int i = str.size() - SoBitDich; i < str.size(); i++)
	{
		str.at(i) = '0';
	}
	des.SetDataBin(str);
	return des;
}

//Dịch phải
QInt operator>>(QInt obj, int SoBitDich)
{
	QInt des;
	string str;
	char MSB = obj.GetDataBin().at(0);
	str = obj.GetDataBin();
	for (int i = str.size() - 1; i > SoBitDich-1; i--)
	{
		str.at(i) = str.at(i-SoBitDich);
	}
	for (int i = 0; i < SoBitDich; i++)
	{
		str.at(i) = MSB;
	}
	des.SetDataBin(str);
	return des;
}

//Quay trái
QInt QInt::rol(int SoBitQuay)
{
	char* BitChuyenRa = new char[SoBitQuay];
	QInt des;
	string str;
	str = this->GetDataBin();
	for (int i = 0, j = SoBitQuay; i < SoBitQuay; i++)
	{
		BitChuyenRa[i] = str.at(j-1);
		j--;
	}
	for (int i = 0; i < str.size() - SoBitQuay; i++)
	{
		str.at(i) = str.at(i + SoBitQuay);
	}
	for (int i = 0; i < SoBitQuay; i++)
	{
		str.at(str.size() - SoBitQuay + i) = BitChuyenRa[i];
	}
	des.SetDataBin(str);
	delete[] BitChuyenRa;
	return des;
}

//Quay phải
QInt QInt::ror(int SoBitQuay)
{
	char* BitChuyenRa = new char[SoBitQuay];
	QInt des;
	string str;
	str = this->GetDataBin();
	for (int i = 0, j = str.size(); i < SoBitQuay; i++)
	{
		BitChuyenRa[i] = str.at(j-1);
		j--;
	}
	for (int i = str.size() - 1; i > SoBitQuay - 1; i--)
	{
		str.at(i) = str.at(i - SoBitQuay);
	}
	for (int i = 0; i < SoBitQuay; i++)
	{
		str.at(i) = BitChuyenRa[i];
	}
	des.SetDataBin(str);
	delete[] BitChuyenRa;
	return des;
}