#include <QApplication>
#include <vector>
#include <memory>
#include "include/lampman.hpp"
#include "include/conf_node.hpp"
#include "include/apache_config.hpp"



int main(int argc, char *argv[])
{
	
	QApplication app(argc, argv);

	Lampman window;
	window.resize(500, 400);
	window.setWindowTitle("Lampman");
	window.show();

	return app.exec();

}
