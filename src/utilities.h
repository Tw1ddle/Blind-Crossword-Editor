#ifndef UTILITIES_H
#define UTILITIES_H

#include <QStringList>
#include <QFile>

namespace Utilities
{
    // Utilities for reading and writing text
    bool readFile(const QString& path, QStringList& text);
    bool writeFile(QFile& file, const QStringList& text);
    bool existsFile(const QString& path);
}

#endif // UTILITIES_H
