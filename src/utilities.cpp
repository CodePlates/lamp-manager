#include "utilities.hpp"

QString run_command(QString command)
{
	QVariantMap args;
	args["command"] = command;
	KAuth::Action commandAction("com.codeplates.lampman.run.command");
	commandAction.setHelperId("com.codeplates.lampman");
	commandAction.setArguments(args);
	KAuth::ExecuteJob *job = commandAction.execute();
	if (!job->exec()) {
	   qDebug() << "KAuth returned an error code:" << job->error();
	   return QString();
	}
	return job->data()["content"].toString();
}

void file_replace(QString filepath, QMap<QString, QVariant> patterns)
{
	QVariantMap args;
	args["filepath"] = filepath;
	args["patterns"] = patterns;

	KAuth::Action commandAction("com.codeplates.lampman.file.replace");
	commandAction.setHelperId("com.codeplates.lampman");
	commandAction.setArguments(args);
	KAuth::ExecuteJob *job = commandAction.execute();
	if (!job->exec()) {
	   qDebug() << "KAuth returned an error code:" << job->error();
	}
}

bool file_write(QString filepath, QString contents)
{
	QVariantMap args;
	args["filepath"] = filepath;
	args["contents"] = contents;

	KAuth::Action commandAction("com.codeplates.lampman.file.write");
	commandAction.setHelperId("com.codeplates.lampman");
	commandAction.setArguments(args);
	KAuth::ExecuteJob *job = commandAction.execute();
	if (!job->exec()) {
	   qDebug() << "KAuth returned an error code:" << job->error();
	   return false;
	}	

	return true;
}

bool file_append(QString filepath, QString contents)
{
	QVariantMap args;
	args["filepath"] = filepath;
	args["contents"] = contents;
	args["append"] = true;

	KAuth::Action commandAction("com.codeplates.lampman.file.write");
	commandAction.setHelperId("com.codeplates.lampman");
	commandAction.setArguments(args);
	KAuth::ExecuteJob *job = commandAction.execute();
	if (!job->exec()) {
	   qDebug() << "KAuth returned an error code:" << job->error();
	   return false;
	}	

	return true;
}

bool file_rename(QString filepath, QString name)
{
	QVariantMap args;
	args["filepath"] = filepath;
	args["name"] = name;

	KAuth::Action commandAction("com.codeplates.lampman.file.rename");
	commandAction.setHelperId("com.codeplates.lampman");
	commandAction.setArguments(args);
	KAuth::ExecuteJob *job = commandAction.execute();
	if (!job->exec()) {
	   qDebug() << "KAuth returned an error code:" << job->error();
	   return false;
	}	

	return true;
}
