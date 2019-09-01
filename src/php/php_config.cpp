#include "php_config.hpp"
#include "utilities.hpp"
#include "apache_config.hpp"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QProcess>
#include <QDebug>

QString get_php_apache_version()
{
	QString version = "Unknown";

	QString modsDir = A2Config::getA2Path("mods-enabled");

	QString result = run_command("ls", {modsDir});
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
	QString result = run_command("php", {"--version"});
	QRegularExpression re("^PHP (\\d+.\\d+(.\\d+)?)-");
	QRegularExpressionMatch match = re.match(result);
	if (match.hasMatch()) {
		version = match.captured(1);
	}
	return version;
}