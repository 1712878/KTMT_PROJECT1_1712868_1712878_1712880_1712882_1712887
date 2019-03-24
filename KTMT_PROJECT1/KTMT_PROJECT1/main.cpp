#include "Qint.h"

int main()
{
	QInt a, b, c;
	a.SetDataDec("123");
	a.PrintQIntBin();
	cout << endl;
	b = a << 2;
	cout << endl;
	b.PrintQIntBin();
	c = a >> 2;
	cout << endl;
	c.PrintQIntBin();
	cout << endl;
	system("pause");
	return 0;
}