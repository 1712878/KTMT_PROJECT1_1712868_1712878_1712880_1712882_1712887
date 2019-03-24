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
	int Exponent = stoi(temp)-16383;
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
	result.insert(result.size(), thapphan);
	if (c == '1')
	{
		temp.insert(0, 1, '-');
	}
	return result;
}

string QFloat::DecToBin(string str) 
{
	string result, intPart, decPart;
	int pos = str.find_first_of('.', 0);
	intPart = str.substr(0, pos);
	decPart = str.substr(pos + 1, str.length() - 1);
	result = ConvertIntPartToBin(intPart) + ConvertDecPartToBin(decPart);
	return string(result);
}

void QFloat::ScanQFloat()
{
	string str;
	cout << "Moi Ban Nhap So Thuc Vao: ";
	getline(cin >> ws, str);
	string bin = this->DecToBin(str);
	this->SetDataBin(str);
}

void QFloat::PrintQFloat()
{
	string bin = this->GetDataBin();
	//cout << this->BinToDec(bin);
	cout << bin;
}