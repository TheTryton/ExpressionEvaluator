#include "CCalculator.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	CCalculator calc;
	calc.show();

	return a.exec();
}
