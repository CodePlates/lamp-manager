#include "include/php_config.hpp"
#include "include/utils.hpp"
#include "include/apache_config.hpp"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QDebug>

QString get_php_apache_version()
{
	QString version = "Unknown";
	QString command = QString("ls %1 | grep php.*.load").arg(A2Config::getA2Path("mods-enabled"));

	QString result = run_command(command.toStdString().c_str());
	QRegularExpression re("^php(\\d+.\\d+(.\\d+)?)\\.load");
	QRegularExpressionMatch match = re.match(result);
	if (match.hasMatch()) {
		version = match.captured(1);
	}
	return version;
}

QString get_php_cli_version()
{
	QString version = "Unknown";
	QString result = run_command("php --version");
	QRegularExpression re("^PHP (\\d+.\\d+(.\\d+)?)-");
	QRegularExpressionMatch match = re.match(result);
	if (match.hasMatch()) {
		version = match.captured(1);
	}
	return version;
}