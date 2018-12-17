#include <QApplication>
#include <vector>
#include <memory>
#include "include/lampman.hpp"
#include "include/apache_config.hpp"



int main(int argc, char *argv[])
{
     // QApplication app(argc, argv);

     // Lampman window;
     // window.resize(500, 400);
     // window.setWindowTitle("Lampman");
     // window.show();

     // return app.exec();

    A2Config a2config;
	//QTextStream out(stdout);

	//  {
	//  	std::vector<std::unique_ptr<Veck>> tree;

	// 	// QStringList* ls1 = new QStringList({"a value", "another one"});
	// 	// QStringList* ls2 = new QStringList({"a value", "another gu guy"});

	// 	Veck* ls1 = new Veck("a value 1");
	// 	Veck* ls2 = new Veck("a value 2");

	// 	std::unique_ptr<Veck> lsPtr1{ls1};
	// 	std::unique_ptr<Veck> lsPtr2{ls2};

	// 	tree.emplace_back(std::move(lsPtr1));
	// 	tree.emplace_back(std::move(lsPtr2));

	// 	ls1->change("Now am three");
	// 	// ls2->append("a third guy");

	// 	// for (auto& ls : tree)
	// 	// {
	// 	// 	for (QString val: *ls)
	// 	// 		out << "   [" << val << "]" << endl;
	// 	// }
	// }

	//out << "out of the boop" << endl;

	//ls2.append("language sir");

	// QMapIterator<QString, QStringList*> iter(tree);

	// while (iter.hasNext()) {
	// 	iter.next();
	// 	out << iter.key() << ": {" << endl;

	// 	for (QString val: *(iter.value()))
	// 		out << "   [" << val << "]" << endl;

	// 	out << "}" << endl;
	// }

}
