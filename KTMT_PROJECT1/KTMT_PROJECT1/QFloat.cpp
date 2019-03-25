#include "QFloat.h"

QFloat::QFloat()
{
	for (int i = 0; i < this->sizeF; i++)
		this->BFloat[i] = 0;
}

string QFloat::BinToDecInt(string bit)
{
	string result = "";
	int len = bit.length();
	for (int i = len - 1; i >= 0; i--)
	{
		if (bit[i] == '1')
			result = AddTwoIntString(result, PositivePowTwo(len - i - 1));
	}
	return result;
}

string QFloat::GetDataBin()
{
	string result;
	result.resize(128);
	for (int i = 0; i < 128; i++)
		result[i] = (GetBit(this->BFloat[i / 32], 31 - i % 32) + '0');
	return result;
}

void QFloat::SetDataBin(string strBin)
{

	for (int i = 0; i < this->sizeF; i++)
		this->BFloat[i] = 0;
	int len = strBin.length();
	for (int i = 0; i < 128; i++)
	{
		len--;
		if (len >= 0 && strBin[len] == '1')
			SetBitOne(this->BFloat[this->sizeF - 1 - i / 32], i % 32);
	}
}

string QFloat::BinToDec(string bit)
{
	char c = bit[0];
	SetDataBin(bit);
	string temp = BinToDecInt(bit.substr(1, 15));
	int Exponent = stoi(temp) - stoi(PositivePowTwo(14)) + 1;
	bit.erase(0, 16);
	bit.insert(0, 1, '1');
	string result =  BinToDecInt(bit.substr(0, Exponent+1));
	result.insert(result.length(), 1, '.');

	string str;
	string thapphan;
	for (int i = Exponent+1; i < bit.length(); i++) {
		if (bit[i] == '1')
		{
			str = NegativePowTwo(i - Exponent);
			str.erase(0, 2);
			thapphan.insert(thapphan.length(), str.length() - thapphan.length(), '0');
			thapphan = AddTwoIntString(thapphan, str);
		}
	}
	if (thapphan.size() == 0)
		thapphan = "0";
	result.insert(result.size(), thapphan);
	if (c == '1')
	{
		result.insert(0, 1, '-');
	}
	return result;
}

string QFloat::DecToBin(string str)
{
	string result, intPart, decPart;
	int pos;
	if (str[0] == '-')
	{
		result += '1';
		str.erase(0, 1);
	}
	else
		result += '0';
	pos = str.find_first_of('.', 0);
	// Chuyển phần nguyên và phần thập phân số thành dạng nhị phân
	intPart = ConvertIntPartToBin(str.substr(0, pos));
	decPart = ConvertDecPartToBin(str.substr(pos + 1, str.length() - 1 - pos));
	str = intPart + decPart;
	// Dùng 15 bits để lưu giá trị exponent biểu diễn dưới dạng số quá k= 2^14 - 1 = 16383
	int lenIntPart, lenDecPart, pointPosition, k = 16383;
	lenIntPart = intPart.length();
	lenDecPart = decPart.length();
	pointPosition = str.find_first_of('1', 0);
	if (pointPosition > -1)
	{
		if (pointPosition >= 0 && pointPosition < lenIntPart)
			k += lenIntPart - pointPosition - 1;

		else
			k += pointPosition - lenDecPart - 1;
		result += ConvertBigIntToBin(to_string(k), 15) + str.substr(pointPosition + 1, str.length() - pointPosition - 1);
		int len = result.length();
		if (len < 128)
			result.append(128 - len, '0');
		else
		{
			if (result[128] == '1')
				result[127] = '1';
			else
				result[127] = '0';
			result = result.substr(0, 128);
		}
	}
	else
	{
		for (int i = 0; i < 128; i++)result[i] = '0';
	}
	return string(result);
}

void QFloat::ScanQFloat()
{
	string str;
	cout << "Moi Ban Nhap So Thuc Vao: ";
	getline(cin >> ws, str);
	string bin = this->DecToBin(str);
	this->SetDataBin(bin);
}

void QFloat::PrintQFloat()
{
	string bin = this->GetDataBin();
	cout << this->BinToDec(bin);
}