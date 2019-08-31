#ifndef UTILITIES_H
#define UTILITIES_H

#include <QString>
#include <QVariantMap>
#include <QMap>
#include <KAuth>
#include <QDebug>

QString run_command(QString command);

void file_replace(QString filepath, QMap<QString, QVariant> patterns);

bool file_write(QString filepath, QString contents);

bool file_append(QString filepath, QString contents);

bool file_rename(QString filepath, QString name);

#endif // UTILITIES_H 