#ifndef __PROCESS_H__
#define __PROCESS_H__

#include "Bit.h"
#include "Process.h"
#include <fstream>

// "123456" + "789" = "124245"
string AddTwoIntString(string num1, string num2);
// Chia một chuỗi dạng 10 cho 2. VD: "123"/2 = "61"
string DivideStringForTwo(string str);
// Chuyển từ chuỗi số nguyên lớn sang chuỗi nhị phân 
string ConvertBigIntToBin(string str, int n);
// "987654321"*2="1975308642"
string MultiplyOneDigit(string str, int factor);
// "123456789"*"987654321"="121932631112635269"
string Multiply(string num1, string num2);
// 2^127 = "170141183460469231731687303715884105728"
string PowOneDigit(int factor, int exp);
// 2^127 = "170141183460469231731687303715884105728"
string PositivePowTwo(int exp);
// 16^10 = "1099511627776"
string PowHex(int exp);
// 2^(-15) = "0.000030517578125"
string NegativePowTwo(int exp);
// '0' -> '1', '1' -> '0'
char NotBit(char &bit);
// Nếu chuỗi bin chưa đủ 128 bit, thêm các bit 0 vào cho đủ
string AddBitZero(string &bin, int n);
// Chuyển chuỗi str về dạng bù 2
string TwoComplement(string &str, int n);
// Chuyển 4bits dạng Bin chuỗi str thành dạng Hex
char ConvertBinToHex(string str);
// Chuyển 1 kí tự dạng Hex thành chuỗi string bin 4 kí tự
string ConvertHexToBin(char c);
string ConvertIntPartToBin(string str);
string ConvertDecPartToBin(string str);
// Chuyển từ dạng B1 sang B2
string ConvertB1ToB2(string str, int B1, int B2);
// Tính toán số decimal
string CalculateDec(string str1, string str2, string Operator);
// Tính toán số binary
string CalculateBin(string str1, string str2, string Operator);
// Tính toán số hexadecimal
string CalculateHex(string str1, string str2, string Operator);
// Tính toán 
string Calculate(string str1, string str2, int Base, string Operator);
// Chuyển số QFloat từ dạng B1 sang B2
string ConvertFloatB1ToB2(string str, int B1, int B2);
// Xử lí file
void FileProcess(ifstream& FileIn, ofstream& FileOut, int type);
#endif // !__PROCESS_H__

