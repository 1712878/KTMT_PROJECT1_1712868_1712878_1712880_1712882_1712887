#include "Process.h"
#include<sstream>
#include<string>

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
string ConvertBigIntToBin(string str, int n)
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
	if (l < n)
		bin.insert(0, n - l, '0');
	return bin;
}
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
string PositivePowTwo(int exp)
{
	return PowOneDigit(2, exp);
}
// 16^10 = "1099511627776"
string PowHex(int exp)
{
	return Multiply(PowOneDigit(4, exp), PowOneDigit(4, exp));
}
// 2^(-15) = "0.000030517578125"
string NegativePowTwo(int exp)
{
	string str = "5";
	for (int i = 1; i < exp; i++)
	{
		str.push_back('0');												//str = "500000000000000"
	}
	for (int i = 1; i < exp; i++)
	{
		str = DivideStringForTwo(str);									//str = "30517578125"
	}
	str.insert(str.begin(), exp - str.size(), '0');						//str = "000030517578125"
	str = "0." + str;													//str = "0.000030517578125"
	return str;
}
// '0' -> '1', '1' -> '0'
char NotBit(char &bit)
{
	if (bit == '0')
		bit = '1';
	else
		bit = '0';
	return bit;
}
// Nếu chuỗi bin chưa đủ 128 bit, thêm các bit 0 vào cho đủ
string AddBitZero(string &bin, int n)
{
	int len = bin.length();
	if (len < n)
		bin.insert(0, n - len, '0');
	return bin;
}

// Chuyển chuỗi str về dạng bù 2
string TwoComplement(string &str, int n)
{
	AddBitZero(str,n);
	int pos = str.find_last_of('1');
	for (int i = 0; i < pos; i++)
		NotBit(str[i]);
	return str;
}
// Chuyển 4bits dạng Bin chuỗi str thành dạng Hex
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

string ConvertHexToBin(char c)
{
	char temp1[] = { '0','1','2','3','4','5','6','7',
					'8','9','A','B','C','D','E','F' };
	string temp2[] = { "0000","0001","0010","0011","0100","0101","0110",
		"0111","1000","1001","1010","1011","1100","1101","1110","1111" };
	int size = sizeof(temp1) / sizeof(char);
	for (int i = 0; i < size; i++)
		if (c == temp1[i])
			return temp2[i];
	return "0000";
}

string ConvertIntPartToBin(string str)
{
	string result;
	bool minus = false;
	if (str[0] == '-')
	{
		minus = true;
		str.erase(str.begin());
	}
	result = ConvertBigIntToBin(str, 16);
	if (minus)
		TwoComplement(result, 16);
	return string(result);
}

string ConvertDecPartToBin(string str)
{
	string result, num = "1";
	int len, pos, i = 0;
	// xử lí số "0123" -> "123"
	pos = str.find_first_not_of('0', 0);
	if (pos == -1)
		return "0";
	str = str.substr(pos, str.length() - pos);

	len = str.length();
	num = num.insert(1, len, '0');
	while (i < 122)
	{
		str = MultiplyOneDigit(str, 2);
		if (str.length() < len + 1)
			result.append(1, '0');
		else
		{
			result.append(1, '1');

			if (str == num)
				break;
			str.erase(0, 1);
			pos = str.find_first_not_of('0', 0);
			str = str.substr(pos, str.length() - pos);
		}
		i++;
	}
	if (i == 126)
		result[125] = '1';
	return string(result);
}
// Loại bỏ số '0'
string FixData(string &str)
{
	int pos = str.find_first_not_of("0");
	if (pos == -1)
		str = "0";
	else
		str.erase(0, pos);
	return str;
}

string ConvertB1ToB2(string str, int B1, int B2)
{
	string result;
	QInt flag;
	if (B1 == 2 & B2 == 10)
		result = flag.BinToDec(str);
	else if (B1 == 2 & B2 == 16)
		result = flag.BinToHex(str);
	else if (B1 == 10 & B2 == 16)
		result = flag.DecToHex(str);
	else if (B1 == 10 & B2 == 2)
		result = flag.DecToBin(str);
	else if (B1 == 16 & B2 == 2)
		result = flag.HexToBin(str);
	else if (B1 == 16 & B2 == 10)
		result = flag.HexToDec(str);
	return FixData(result);
}

string CalculateDec(string str1, string str2, string Operator)
{
	QInt obj1;
	QInt obj2;
	QInt des;
	obj1.SetDataDec(str1);
	obj2.SetDataDec(str2);
	if (Operator == "+")
	{
		des = obj1 + obj2;
	}
	else if (Operator == "-")
	{
		des = obj1 - obj2;
	}
	else if (Operator == "*")
	{
		des = obj1 * obj2;
	}
	else if (Operator == "/")
	{
		des = obj1 / obj2;
	}
	else if (Operator == ">>")
	{
		des = obj1 >> stoi(str2);
	}
	else if (Operator == "<<")
	{
		des = obj1 << stoi(str2);
	}
	else if (Operator == "ror")
	{
		des = obj1.ror(stoi(str2));
	}
	else if (Operator == "rol")
	{
		des = obj1.rol(stoi(str2));
	}
	else if (Operator == "&")
	{
		des = obj1 & obj2;
	}
	else if (Operator == "|")
	{
		des = obj1 | obj2;
	}
	else if (Operator == "^")
	{
		des = obj1 ^ obj2;
	}
	return des.GetDataDec();
}

string CalculateBin(string str1, string str2, string Operator)
{
	QInt obj1;
	QInt obj2;
	QInt des;
	obj1.SetDataBin(str1);
	obj2.SetDataBin(str2);
	if (Operator == "+")
	{
		des = obj1 + obj2;
	}
	else if (Operator == "-")
	{
		des = obj1 - obj2;
	}
	else if (Operator == "*")
	{
		des = obj1 * obj2;
	}
	else if (Operator == "/")
	{
		des = obj1 / obj2;
	}
	else if (Operator == ">>")
	{
		des = obj1 >> stoi(str2);
	}
	else if (Operator == "<<")
	{
		des = obj1 << stoi(str2);
	}
	else if (Operator == "ror")
	{
		des = obj1.ror(stoi(str2));
	}
	else if (Operator == "rol")
	{
		des = obj1.rol(stoi(str2));
	}
	else if (Operator == "&")
	{
		des = obj1 & obj2;
	}
	else if (Operator == "|")
	{
		des = obj1 | obj2;
	}
	else if (Operator == "^")
	{
		des = obj1 ^ obj2;
	}
	return des.GetDataBit();
}

string CalculateHex(string str1, string str2, string Operator)
{
	QInt obj1;
	QInt obj2;
	QInt des;
	obj1.SetDataHex(str1);
	obj2.SetDataHex(str2);
	if (Operator == "+")
	{
		des = obj1 + obj2;
	}
	else if (Operator == "-")
	{
		des = obj1 - obj2;
	}
	else if (Operator == "*")
	{
		des = obj1 * obj2;
	}
	else if (Operator == "/")
	{
		des = obj1 / obj2;
	}
	else if (Operator == ">>")
	{
		des = obj1 >> stoi(str2);
	}
	else if (Operator == "<<")
	{
		des = obj1 << stoi(str2);
	}
	else if (Operator == "ror")
	{
		des = obj1.ror(stoi(str2));
	}
	else if (Operator == "rol")
	{
		des = obj1.rol(stoi(str2));
	}
	else if (Operator == "&")
	{
		des = obj1 & obj2;
	}
	else if (Operator == "|")
	{
		des = obj1 | obj2;
	}
	else if (Operator == "^")
	{
		des = obj1 ^ obj2;
	}
	return des.GetDataHex();
}

string Calculate(string str1, string str2, int Base, string Operator)
{
	string des;
	switch (Base)
	{
	case 2:
		des = CalculateBin(str1, str2, Operator); break;
	case 10:
		des = CalculateDec(str1, str2, Operator); break;
	case 16:
		des = CalculateHex(str1, str2, Operator); break;
	}
	return des;
}

string ConvertFloatB1ToB2(string str, int B1, int B2)
{
	QFloat flag;
	if (B1 == 2 & B2 == 10)
		return flag.BinToDec(str);
	if (B1 == 10 & B2 == 2)
		return flag.DecToBin(str);
}
int Count(string str)
{
	int result=0, len = str.length();
	for (int i = 0; i < len; i++)
	{
		if (str[i] == ' ')
			result++;
	}
	return result;
}
void FileProcess(ifstream& FileIn, ofstream& FileOut, int type)
{
	if (!FileIn.is_open())
	{
		cout << "Khong the mo file input!" << endl;
		system("pause");
		return;
	}
	if (type == 1)
	{
		int B1, B2;
		string str1,Operator,str2;
		while (!FileIn.eof())
		{
			string s;
			getline(FileIn, s);
			stringstream ss(s);
			if (Count(s) == 2)
			{
				ss >> B1 >> B2;
				ss >> str1;
				FileOut << ConvertB1ToB2(str1, B1, B2) << "\n";
			}
			else
			{
				ss >> B1;
				ss >> str1;
				ss >> Operator;
				ss >> str2;
				FileOut << Calculate(str1, str2, B1, Operator) << "\n";
			}
		}
	}
	else if (type == 2)
	{
		int b1, b2;
		string str;
		while (!FileIn.eof())
		{
			getline(FileIn, str);
			stringstream ss(str);
			ss >> b1;
			ss >> b2;
			ss >> str;
			FileOut << ConvertFloatB1ToB2(str, b1, b2) << "\n";
		}
	}
	else
	{
		cout << "\nType error!\n";
	}
}
