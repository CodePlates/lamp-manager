#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QDebug>
#include <QObject>
#include <KAuth>


class LampmanHelper : public QObject
{
   Q_OBJECT
public Q_SLOTS:
   KAuth::ActionReply file_replace(const QVariantMap& args);
   KAuth::ActionReply file_write(const QVariantMap& args);
   KAuth::ActionReply file_rename(const QVariantMap& args);
   KAuth::ActionReply run_command(const QVariantMap& args);
};

KAuth::ActionReply LampmanHelper::file_write(const QVariantMap &args){
	KAuth::ActionReply reply;
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
   	reply = KAuth::ActionReply::HelperErrorReply();
   	reply.setErrorDescription(file.errorString());
   }

   return reply;
}

KAuth::ActionReply LampmanHelper::file_rename(const QVariantMap &args){
	KAuth::ActionReply reply;
	QString filepath = args["filepath"].toString();
	QString name = args["name"].toString();

	QFile file(filepath);
	if (!file.rename(name)) {
   	reply = KAuth::ActionReply::HelperErrorReply();
   	reply.setErrorDescription(file.errorString());
   }

   return reply;
}

KAuth::ActionReply LampmanHelper::file_replace(const QVariantMap &args){
	KAuth::ActionReply reply;
	QString filepath = args["filepath"].toString();
	QMap<QString, QVariant> patterns = args["patterns"].toMap();

	QFile file(filepath);
	QFileInfo fileinfo(filepath);
	QString tmpFile = QDir::tempPath().append("/").append(fileinfo.fileName());
	QFile filetmp(tmpFile);

	if(!file.open(QIODevice::ReadOnly)){
	   reply = KAuth::ActionReply::HelperErrorReply();
	   reply.setErrorDescription(file.errorString());
	}else if (!filetmp.open(QIODevice::WriteOnly)){
	   reply = KAuth::ActionReply::HelperErrorReply();
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

KAuth::ActionReply LampmanHelper::run_command(const QVariantMap &args)
{
	KAuth::ActionReply reply;
	const char* command = args["command"].toString().toStdString().c_str();

	QString data;
	char buffer[256];
	FILE* stream = popen(command, "r");
	if (stream) {
		while (!feof(stream)) {
			if (fgets(buffer, 256, stream) != NULL) 
				data.append(buffer);
		}
		pclose(stream);
		QVariantMap map;
		map["content"] = QVariant(data);
      reply.setData(map);
	} else {
		reply = KAuth::ActionReply::HelperErrorReply();
		reply.setErrorDescription("Unable to run command: ");
	}

	return reply;
}

#include "helpers.moc"
KAUTH_HELPER_MAIN("com.codeplates.lampman", LampmanHelper)