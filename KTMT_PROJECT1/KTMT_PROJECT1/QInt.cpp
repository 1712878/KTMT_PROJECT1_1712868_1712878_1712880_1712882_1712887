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
	return bin;
}

QInt::QInt()
{
	for (int i = 0; i < this->size; i++)
		this->data[i] = 0;
}

void QInt::SetDataBin(string strBin)
{
	int len = strBin.length();
	for (int i = 0; i < 128; i++)
	{
		len--;
		if (len >= 0 && strBin[len] == '1')
			SetBit(this->data[this->size - 1 - i / 32], i % 32);
	}
}

void QInt::SetDataDec(string strDec)
{
	string bin = ConvertBigIntToBin(strDec);
	this->SetDataBin(bin);
}

void QInt::PrintQIntBit()
{
	for (int i = 0; i < this->size; i++)
	{
		PrintIntBit(this->data[i]);
	}
}
string QInt::GetDataBin()
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

// END
void QInt::PrintQInt()
{
	
}

string QInt::DecToBin(string str)
{
	return string();
}

string QInt::BinToDec(string bit)
{
	return string();
}

string QInt::BinToHex(string bit)
{
	return string();
}

string QInt::DecToHex(string str)
{
	return string();
}

QInt QInt::operator+(const QInt & obj)
{
	return QInt();
}

QInt QInt::operator-(const QInt & obj)
{
	return QInt();
}

QInt QInt::operator*(const QInt & obj)
{
	return QInt();
}

QInt QInt::operator/(const QInt & obj)
{
	return QInt();
}

bool QInt::operator<(const QInt & obj)
{
	return false;
}

bool QInt::operator>(const QInt & obj)
{
	return false;
}

bool QInt::operator==(const QInt & obj)
{
	return false;
}

bool QInt::operator<=(const QInt & obj)
{
	return false;
}

bool QInt::operator>=(const QInt & obj)
{
	return false;
}

bool QInt::operator=(const QInt & obj)
{
	return false;
}

bool QInt::operator&(const QInt & obj)
{
	return false;
}

bool QInt::operator|(const QInt & obj)
{
	return false;
}

bool QInt::operator^(const QInt & obj)
{
	return false;
}

//bool QInt::operator~(const QInt & obj)
//{
//	return false;
//}

QInt QInt::operator<<(const QInt & obj)
{
	return QInt();
}

QInt QInt::operator>>(const QInt & obj)
{
	return QInt();
}

//QInt::operator rol(const QInt & obj)
//{
//}

//QInt::operator ror(const QInt & obj)
//{
//}

