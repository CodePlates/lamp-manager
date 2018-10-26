#include <QApplication>
#include "include/lampman.hpp"


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	Lampman window;
	window.resize(500, 400);
	window.setWindowTitle("Lampman");
	window.show();

	return app.exec();
}