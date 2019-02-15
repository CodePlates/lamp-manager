#include "include/utils.hpp"

bool file_replace(QString filepath, PatternsList patterns){
	QFile file(filepath);
	QFileInfo fileinfo(filepath);
	if (!file.open(QIODevice::ReadOnly)) {
		qWarning("Cannot open file");
		return false;
	}

	QFile filetmp(QDir::tempPath().append("/").append(fileinfo.fileName()));
	if (!filetmp.open(QIODevice::WriteOnly)) {
    	return false;
   }

	QTextStream in(&file);
	QTextStream outstream(&filetmp);

	QList<QRegularExpression> regs;
	for (auto pattern : patterns) {
		QRegularExpression re(pattern.first, QRegularExpression::MultilineOption);
		regs.append(re);
	}

	QString contents = in.readAll();
	if (contents.at(contents.length() - 1) != '\n') contents.append('\n');
	for (int i = 0; i < patterns.length(); i++) {
		contents.replace(regs.at(i), patterns.at(i).second);
	}
	outstream << contents;
	
	file.close();
   filetmp.close();
   file.remove();
   filetmp.rename(fileinfo.absoluteFilePath());
   return true;
}