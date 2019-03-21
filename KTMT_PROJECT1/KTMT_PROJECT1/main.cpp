#include "Qint.h"

int main()
{
	QInt a, b;
	a.ScanQInt();
	b.ScanQInt();
	(a - b).PrintQInt();
	system("pause");
	return 0;
}