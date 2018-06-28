#include <QApplication>
#include "CUserInput.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	CUserInput input;
	input.show();

	return app.exec();
}
