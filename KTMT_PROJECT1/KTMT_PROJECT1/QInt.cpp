#include "Qint.h"

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

Qint::Qint()
{
	for (int i = 0; i < this->size; i++)
		this->data[i] = 0;
}

void Qint::SetDataBin(string strBin)
{
	int len = strBin.length();
	for (int i = 0; i < 128; i++)
	{
		len--;
		if (len >= 0 && strBin[len] == '1')
			SetBit(this->data[this->size - 1 - i / 32], i % 32);
	}
}

void Qint::SetDataDec(string strDec)
{
	string bin = ConvertBigIntToBin(strDec);
	this->SetDataBin(bin);
}

void Qint::PrintQintBit()
{
	for (int i = 0; i < this->size; i++)
	{
		PrintIntBit(this->data[i]);
	}
}
void Qint::ScanQint(Qint & x)
{
	string str;
	cout << "Moi Ban Nhap So Vao: ";
	getline(cin >> ws, str);
	x.SetDataDec(str);
}

