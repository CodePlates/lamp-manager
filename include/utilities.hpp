#ifndef UTILITIES_H
#define UTILITIES_H

#include <QString>
#include <QStringList>
#include <QVariantMap>
#include <QMap>
#include <KAuth>
#include <QDebug>

QString run_command(QString command, QStringList options = QStringList(), bool asRoot = false);

void file_replace(QString filepath, QMap<QString, QVariant> patterns);

bool file_write(QString filepath, QString contents);

bool file_append(QString filepath, QString contents);

bool file_rename(QString filepath, QString name);

QString file_read(QString filepath);

#endif // UTILITIES_H 