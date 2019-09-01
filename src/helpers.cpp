#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QProcess>
#include <QDebug>
#include <QObject>
#include <KAuth>

using namespace KAuth;

class LampmanHelper : public QObject
{
   Q_OBJECT
protected:
   ActionReply file_replace(const QVariantMap& args);
   ActionReply file_write(const QVariantMap& args);
   ActionReply file_rename(const QVariantMap& args);
   ActionReply file_read(const QVariantMap& args);
   ActionReply run_command(const QVariantMap& args);

public Q_SLOTS:
   ActionReply dispatch(const QVariantMap& args);
};

ActionReply LampmanHelper::dispatch(const QVariantMap& args)
{
	QString action = args["action"].toString();
	if (action == "file_write")
		return file_write(args);
	else if (action == "file_rename")
		return file_rename(args);
	else if (action == "file_read")
		return file_read(args);
	else if (action == "file_replace")
		return file_replace(args);
	else if (action == "run_command")
		return run_command(args);
}

ActionReply LampmanHelper::file_write(const QVariantMap &args) 
{
	ActionReply reply;
	QString filepath = args["filepath"].toString();
	QString contents = args["contents"].toString();
	bool append = args.value("append", false).toBool();

	QFile file(filepath);

	if (!append && file.open(QIODevice::WriteOnly)) {
    	QTextStream outstream(&file);
    	outstream << contents;
    	file.close();
   }else if (append && file.open(QIODevice::ReadWrite | QIODevice::Append)) {
    	QTextStream outstream(&file);
    	outstream.seek(outstream.pos() - 1);
    	if (QString::compare(outstream.read(1), "\n") != 0){
    		outstream << "\n";
    	}
    	outstream << contents << "\n";
    	file.close();
   } else {
   	reply = ActionReply::HelperErrorReply();
   	reply.setErrorDescription(file.errorString());
   }

   return reply;
}

ActionReply LampmanHelper::file_rename(const QVariantMap &args)
{
	ActionReply reply;
	QString filepath = args["filepath"].toString();
	QString name = args["name"].toString();

	QFile file(filepath);
	if (!file.rename(name)) {
   	reply = ActionReply::HelperErrorReply();
   	reply.setErrorDescription(file.errorString());
   }

   return reply;
}

ActionReply LampmanHelper::file_read(const QVariantMap &args) 
{
	ActionReply reply;
	QString filepath = args["filepath"].toString();

	QFile file(filepath);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		reply = ActionReply::HelperErrorReply();
		reply.setErrorDescription(file.errorString());
   }else {
		QTextStream in(&file);
		QString contents = in.readAll();
		QVariantMap map;
		map["content"] = QVariant(contents);
      reply.setData(map);
   }

   return reply;
}

ActionReply LampmanHelper::file_replace(const QVariantMap &args) 
{
	ActionReply reply;
	QString filepath = args["filepath"].toString();
	QMap<QString, QVariant> patterns = args["patterns"].toMap();

	QFile file(filepath);
	QFileInfo fileinfo(filepath);
	QString tmpFile = QDir::tempPath().append("/").append(fileinfo.fileName());
	QFile filetmp(tmpFile);

	if(!file.open(QIODevice::ReadOnly)){
	   reply = ActionReply::HelperErrorReply();
	   reply.setErrorDescription(file.errorString());
	}else if (!filetmp.open(QIODevice::WriteOnly)){
	   reply = ActionReply::HelperErrorReply();
	   reply.setErrorDescription(filetmp.errorString());
	}else{
		QTextStream in(&file);
		QTextStream outstream(&filetmp);

		QString contents = in.readAll();
		if (contents.at(contents.length() - 1) != '\n') contents.append('\n');

		for (auto pattern : patterns.keys()) {
			QRegularExpression re(pattern, QRegularExpression::MultilineOption);
			contents.replace(re, patterns.value(pattern).toString());
		}
	
		outstream << contents;
		
		file.close();
	   filetmp.close();
	   file.remove();
	   filetmp.rename(fileinfo.absoluteFilePath());
	}

	return reply;
}

ActionReply LampmanHelper::run_command(const QVariantMap &args)
{
	ActionReply reply;
	QString command = args["command"].toString();
	QStringList opts = args["options"].toStringList();

	QProcess term;
	term.start(command, opts);

	if (!term.waitForFinished(-1)) {
		reply = ActionReply::HelperErrorReply();
		qDebug() << command << " :: " << opts;
		qDebug() << "Exit Code: " << term.exitCode();
		reply.setErrorDescription("Unable to run sh!");
	}else {
		QVariantMap map;
		map["content"] = QString(term.readAllStandardOutput());
   	reply.setData(map);
	}

	return reply;
}

#include "helpers.moc"
KAUTH_HELPER_MAIN("com.codeplates.lampman", LampmanHelper)