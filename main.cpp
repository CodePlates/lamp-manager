#include <QApplication>
#include <vector>
#include <memory>
#include "include/lampman.hpp"
#include <QTextStream>

int main(int argc, char *argv[])
{
	
	QApplication app(argc, argv);

// 	if ( geteuid() ) {NotSudoDialog *sw = new NotSudoDialog; sw->show();}
// else {MainWindow *kt = new MainWindow; kt->show(); }
	Lampman window;
	window.resize(500, 400);
	window.setWindowTitle("Lampman");
	window.show();

	return app.exec();

}
