#include "QInt.h"

// "123456" + "789" = "124245"
string AddTwoIntString(string num1, string num2)
{
	// num1 = 12345    num2 = 678901
	int len1 = num1.size(), len2 = num2.size(), len;
	if (len1 > len2)
		num2.insert(0, len1 - len2, '0');
	if (len1 < len2)
		num1.insert(0, len2 - len1, '0');
	len = num1.size();
	int tmp, tmp1, tmp2, flag = 0;
	string result = "";
	for (int i = len - 1; i >= 0; i--)
	{
		tmp1 = num1[i] - '0';
		tmp2 = num2[i] - '0';
		tmp = tmp1 + tmp2 + flag;
		if (tmp > 9)flag = 1;
		else flag = 0;
		result = to_string(tmp % 10) + result;
	}
	if (flag == 1)
		result = '1' + result;
	return result;
}
// Chia một chuỗi dạng 10 cho 2. VD: "123"/2 = "61"
string DivideStringForTwo(string str)
{
	string thuong;
	int len = str.size();
	int du = str[0] - '0', i = 0, j;
	while (i <= len - 1)
	{
		for (j = 1; j <= 10; j++)
		{
			if (2 * j > du)
			{
				thuong.append(1, j - 1 + '0');
				du = du - 2 * (j - 1);
				break;
			}
		}
		i++;
		du = du * 10 + str[i] - '0';
	}
	int pos = thuong.find_first_not_of('0');
	if (pos < 0)pos = 0;
	thuong = thuong.substr(pos, thuong.size() - pos);
	if (thuong.size() == 0)thuong += '0';
	return thuong;
}
// Chuyển từ chuỗi số nguyên lớn sang chuỗi nhị phân 
string ConvertBigIntToBin(string str)
{
	string tmp = str;
	int len = tmp.size();
	string bin;
	char c;
	while (tmp != "0")
	{
		c = (tmp[len - 1] - '0') % 2;
		bin.insert(0, to_string(c));
		tmp = DivideStringForTwo(tmp);
		len = tmp.size();
	}
	int l = bin.length();
	if (l < 128)
		bin.insert(0, 128 - l, '0');
	return bin;
}

QInt::QInt()
{
	for (int i = 0; i < this->size; i++)
		this->data[i] = 0;
}

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

void QInt::SetDataDec(string strDec)
{
	string bin = this->DecToBin(strDec);
	this->SetDataBin(bin);
}

void QInt::PrintQIntBit()
{
	for (int i = 0; i < this->size; i++)
	{
		PrintIntBit(this->data[i]);
	}
}
string QInt::GetDataBin() const
{
	string ssr;
	int len = 127;
	ssr.resize(128);
	bool strBin[128];
	for (int i = 0; i <128; i++)
	{
		strBin[i]=GetBit(this->data[this->size - 1 - i / 32], i % 32);
		
	}
	for (int i = 0; i < 128; i++)
	{
		ssr[len-i] = strBin[i] + '0';
	}
	return ssr;
}
void QInt::ScanQInt()
{
	string str;
	cout << "Moi Ban Nhap So Vao: ";
	getline(cin >> ws, str);
	this->SetDataDec(str);
}
// BEGIN

// "987654321"*2="1975308642"
string MultiplyOneDigit(string str, int factor)
{
	if (factor < 1 || factor > 9)
		return "0";
	string result = "";
	int len = str.length();
	int rem = 0;
	int temp;
	for (int i = len - 1; i >= 0; i--)
	{
		temp = factor * (str[i] - '0') + rem;
		rem = 0;
		if (temp >= 10)
		{
			rem = temp / 10;
			temp -= rem * 10;
		}
		result.insert(0, to_string(temp));
	}
	if (rem)
		result.insert(0, to_string(rem));
	return result;
}
// "123456789"*"987654321"="121932631112635269"
string Multiply(string num1, string num2)
{
	string result = "";
	int len = num2.length();
	int factor;
	string temp;
	for (int i = len - 1; i >= 0; i--)
	{
		factor = num2[i] - '0';
		temp = MultiplyOneDigit(num1, factor);
		temp.insert(temp.length(), len - i - 1, '0');
		result = AddTwoIntString(result, temp);
	}
	return result;
}
// 2^127 = "170141183460469231731687303715884105728"
string PowOneDigit(int factor, int exp)
{
	if (exp == 0)
		return "1";
	string result = to_string(factor);
	while (--exp)
		result = MultiplyOneDigit(result, factor);
	return result;
}
// 2^127 = "170141183460469231731687303715884105728"
string PowTwo(int exp)
{
	return PowOneDigit(2, exp);
}
// 16^10 = 1099511627776
string PowHex(int exp)
{
	return Multiply(PowOneDigit(4, exp), PowOneDigit(4, exp));
}
//
void NotBit(char &bit)
{
	if (bit == '0')
		bit = '1';
	else
		bit = '0';
}
//
string AddBitZero(string &bin)
{
	int len = bin.length();
	if (len < 128)
		bin.insert(0, 128 - len, '0');
	return bin;
}
// Không dấu
string NotSign(string &str)
{
	int pos = str.find_last_of('1');
	for (int i = 0; i < pos; i++)
		NotBit(str[i]);
	return str;
}
// Bù 2
string TwoComplement(string &str)
{
	AddBitZero(str);
	NotSign(str);
	return str;
}
//
char ConvertBinToHex(string str)
{
	char temp1[] = { '0','1','2','3','4','5','6','7',
					'8','9','A','B','C','D','E','F' };
	string temp2[] = { "0000","0001","0010","0011","0100","0101","0110",
		"0111","1000","1001","1010","1011","1100","1101","1110","1111" };
	int size = sizeof(temp1) / sizeof(char);
	for (int i = 0; i < size; i++)
		if (str == temp2[i])
			return temp1[i];
	return '0';
}
// END
void QInt::PrintQInt()
{
	string temp = this->GetDataBin();
	cout << this->BinToDec(temp);
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
	result = ConvertBigIntToBin(str);
	if (minus)
		TwoComplement(result);
	return result;
}

string QInt::BinToDec(string bit)
{
	AddBitZero(bit);
	string result = "";
	bool minus = false;
	if (bit[0] == '1')
	{
		minus = true;
		NotSign(bit);
	}
	bit.erase(bit.begin());
	int len = bit.length();
	for (int i = len - 1; i >= 0; i--)
	{
		if(bit[i] == '1')
			result = AddTwoIntString(result, PowTwo(len - i - 1));
	}
	if (minus)
		result.insert(0, 1, '-');
	return result;
}

string QInt::BinToHex(string bit)
{
	AddBitZero(bit);
	string result = "";
	bool minus = false;
	if (bit[0] == '1')
	{
		minus = true;
		NotSign(bit);
	}
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
	if (minus)
		result.insert(0, 1, '-');
	return result;
}

string QInt::DecToHex(string str)
{
	string result;
	result = this->DecToBin(str);
	result = this->BinToHex(result);
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

bool QInt::operator<(const QInt & obj)
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

bool QInt::operator>(const QInt & obj)
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

bool QInt::operator==(const QInt & obj)
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

bool QInt::operator<=(const QInt & obj)
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

bool QInt::operator>=(const QInt & obj)
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

QInt QInt::operator=(const QInt &obj)
{
	string a;
	string temp = obj.GetDataBin();
	this->SetDataBin(temp);
	return*this;
}

QInt & operator&(const QInt & obj, const QInt & Kobj)
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

QInt & operator|(const QInt & obj, const QInt & Kobj)
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

QInt & operator^(const QInt & obj, const QInt & Kobj)
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

QInt & operator~(const QInt & obj)
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

