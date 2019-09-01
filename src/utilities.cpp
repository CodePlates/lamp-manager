#include "utilities.hpp"

QString run_command(QString command, QStringList options)
{
	QVariantMap args;
	args["command"] = command;
	args["options"] = options;
	args["action"] = "run_command";

	KAuth::Action commandAction("com.codeplates.lampman.dispatch");
	commandAction.setHelperId("com.codeplates.lampman");
	commandAction.setArguments(args);
	KAuth::ExecuteJob *job = commandAction.execute();
	if (!job->exec()) {
	   qDebug() << "KAuth(run command) returned an error code:" << job->error();
	   qDebug() << "Message: " << job->errorString();
	   return QString();
	}
	return job->data()["content"].toString();
}

void file_replace(QString filepath, QMap<QString, QVariant> patterns)
{
	QVariantMap args;
	args["filepath"] = filepath;
	args["patterns"] = patterns;
	args["action"] = "file_replace";

	KAuth::Action commandAction("com.codeplates.lampman.dispatch");
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
	args["action"] = "file_write";

	KAuth::Action commandAction("com.codeplates.lampman.dispatch");
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
	args["action"] = "file_append";

	KAuth::Action commandAction("com.codeplates.lampman.dispatch");
	commandAction.setHelperId("com.codeplates.lampman");
	commandAction.setArguments(args);
	KAuth::ExecuteJob *job = commandAction.execute();
	if (!job->exec()) {
	   qDebug() << "KAuth returned an error code:" << job->error();
	   return false;
	}	

	return true;
}

QString file_read(QString filepath)
{
	// qDebug() << "Reading: " << filepath;
	QVariantMap args;
	args["filepath"] = filepath;
	args["action"] = "file_read";

	KAuth::Action commandAction("com.codeplates.lampman.dispatch");
	commandAction.setHelperId("com.codeplates.lampman");
	commandAction.setArguments(args);
	KAuth::ExecuteJob *job = commandAction.execute();
	if (!job->exec()) {
	   qDebug() << "KAuth returned an error:" << job->errorString();
	   return QString();
	}	

	return job->data()["content"].toString();
}

bool file_rename(QString filepath, QString name)
{
	QVariantMap args;
	args["filepath"] = filepath;
	args["name"] = name;
	args["action"] = "file_rename";

	KAuth::Action commandAction("com.codeplates.lampman.dispatch");
	commandAction.setHelperId("com.codeplates.lampman");
	commandAction.setArguments(args);
	KAuth::ExecuteJob *job = commandAction.execute();
	if (!job->exec()) {
	   qDebug() << "KAuth returned an error code:" << job->error();
	   return false;
	}	

	return true;
}
