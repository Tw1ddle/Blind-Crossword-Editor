#ifndef UTILITIES_H
#define UTILITIES_H

#include <QStringList>
#include <QFile>
#include <QUrl>
#include <QDir>

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

    // Filesystem
    QString getApplicationDirPath();

    // Gets all the filenames of files in the directory, but not that of folders
    QStringList getFilenamesInDirectory(const QDir& directory);

    // Gets all the filepaths of files in the directory, but not that of folders
    QStringList getFilepathsInDirectory(const QDir& directory);

    // Return file paths/names that match the given file extension
    const QStringList filterByExtension(const QStringList& filenames, const QString& extension);

    // Creates a Qt file dialog file filter that shows only the permitted file extensions given
    const QString createNameFilter(const QString& title, const QStringList& permittedFormats);
}

#endif // UTILITIES_H
