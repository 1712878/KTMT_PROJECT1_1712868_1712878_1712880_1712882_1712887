#include "Qfloat.h"


string Qfloat::BinToDecInt(string bit)
{
	string result = "";
	bool minus = false;
	if (bit[0] == '1')
	{
		minus = true;
		TwoComplement(bit);
	}
	bit.erase(bit.begin());
	int len = bit.length();
	for (int i = len - 1; i >= 0; i--)
	{
		if (bit[i] == '1')
			result = AddTwoIntString(result, PowTwo(len - i - 1));
	}
	if (minus)
		result.insert(0, 1, '-');
	return result;
}

void Qfloat::SetDataBin(string strBin)
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

Qfloat Qfloat::BinToDec(string bit)
{
	SetDataBin(bit);
	string tempint = bit.substr(0, 15);
	string temp = BinToDecInt(tempint);
	temp.insert(temp.length(), 1, ',');

	return Qfloat();
}

string Qfloat::DecToBin(Qfloat x)
{
	return string();
}

void Qfloat::ScanQfloat(Qfloat & x)
{
}

void Qfloat::PrintQfloat(Qfloat x)
{
}

Qfloat::Qfloat()
{
	for (int i = 0; i < this->sizeF; i++)
		this->BFloat[i] = 0;
}


Qfloat::~Qfloat()
{
}