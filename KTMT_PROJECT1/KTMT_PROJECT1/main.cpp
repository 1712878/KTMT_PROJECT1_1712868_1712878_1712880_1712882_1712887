#include "Qint.h"

int main()
{
	QInt a, b;
	a.ScanQInt(); cout << a.GetDataBin() << endl;
	b.ScanQInt(); cout << b.GetDataBin() << endl;
	QInt c = a * b;
	cout << c.GetDataBin() << endl;
	system("pause");
	return 0;
}