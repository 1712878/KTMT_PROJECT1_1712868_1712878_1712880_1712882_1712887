#include "Qint.h"
#include "QFloat.h"

int main(int argc, char* argv[])
{
	string FileIn, FileOut;
	int type;
	if (argc > 3)
	{
		FileIn = argv[1];
		FileOut = argv[2];
		type = argv[3][0];
	}
	else
	{
		cout << "\nThieu tham so!\n";
	}
	ifstream input;
	ofstream output;
	input.open(FileIn,ios::in);
	output.open(FileOut,ios::out);
	FileProcess(input, output, type);
	input.close();
	output.close();
	system("pause");
	return 0;
}