#pragma once

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QDebug>

typedef QList<QPair<QString,QString>> PatternsList;

bool file_replace(QString filepath, PatternsList patterns);

QString run_command(const char* command);