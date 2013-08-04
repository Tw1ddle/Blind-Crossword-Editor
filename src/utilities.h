#ifndef UTILITIES_H
#define UTILITIES_H

#include <QStringList>
#include <QFile>
#include <QUrl>

namespace Utilities
{
    // Utilities for reading and writing text
    bool readFile(const QString& path, QStringList& text);
    bool writeFile(QFile& file, const QStringList& text);
    bool existsFile(const QString& path);
    bool openUrl(const QUrl& url);

    // QString checked conversions
    int toInt(const QString& str);
    unsigned int toUInt(const QString& str);
}

#endif // UTILITIES_H
