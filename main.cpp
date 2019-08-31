#include <QApplication>
#include <memory>
#include "lampman.hpp"
#include <unistd.h>
#include <QDebug>

#include "apache_scanner.hpp"
#include "apache_parser.hpp"


int main(int argc, char *argv[])
{
	
	QApplication app(argc, argv);

	if (geteuid()) {
		qWarning("You need to run this program as root");
	}
// 	if ( geteuid() ) {NotSudoDialog *sw = new NotSudoDialog; sw->show();}
// else {MainWindow *kt = new MainWindow; kt->show(); }
	Lampman window;
	window.resize(500, 400);
	window.setWindowTitle("Lampman");
	window.show();

	return app.exec();

		
}
