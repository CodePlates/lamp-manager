#include <QApplication>
#include <QWidget>
#include <memory>
#include "lampman.hpp"
#include <utilities.hpp>
#include <QDebug>

#include "apache_scanner.hpp"
#include "apache_parser.hpp"


int main(int argc, char *argv[])
{
	
	QApplication app(argc, argv);
	
	Lampman window;
	window.resize(500, 400);
	window.setWindowTitle("Lampman");
	window.show();


	return app.exec();

		
}
