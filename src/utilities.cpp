#include "utilities.h"

#include <QTextStream>
#include <QDesktopServices>
#include <QUrl>
#include <QCoreApplication>

namespace Utilities
{

bool readFile(const QString& path, QStringList& text)
{
    // Note that QFile expects the file separator to be '/' regardless of operating system.

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return false;
    }

    QTextStream in(&file);
    if(in.atEnd() || (in.status() != QTextStream::Ok))
    {
        return false;
    }

    QString currentLine;
    do
    {
        currentLine = in.readLine();
        if(currentLine.length() != 0) //skips empty lines
        {
            text << currentLine;
        }
    } while (!currentLine.isNull());

    return true;
}

bool writeFile(QFile& file, const QStringList& text)
{
    if(!file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text))
    {
        return false;
    }

    QTextStream out(&file);

    for(QString line : text)
    {
        out << line << endl;
    }

    if(out.status() == QTextStream::Ok)
    {
        return true;
    }

    return false;
}

bool existsFile(const QString& path)
{
    QFile file(path);

    return file.exists();
}

bool openUrl(const QUrl& url)
{
    return QDesktopServices::openUrl(url);
}

int toInt(const QString& str)
{
    bool ok;

    int value = str.toInt(&ok);

    Q_ASSERT(ok);

    return value;
}

unsigned int toUInt(const QString& str)
{
    bool ok;

    int value = str.toUInt(&ok);

    Q_ASSERT(ok);

    return value;
}

QString getApplicationDirPath()
{
    return QCoreApplication::applicationDirPath();
}

QStringList getFilenamesInDirectory(const QDir& directory)
{
    auto fileNames = directory.entryList(QDir::NoDotAndDotDot | QDir::Files);

    return fileNames;
}

QStringList getFilepathsInDirectory(const QDir& directory)
{
    auto fileNames = directory.entryList(QDir::NoDotAndDotDot | QDir::Files);

    QStringList filepaths;
    for(auto& file : fileNames)
    {
        filepaths.append(directory.absoluteFilePath(file));
    }

    return filepaths;
}

const QStringList filterByExtension(const QStringList& filenames, const QString& extension)
{
    auto filteredList = filenames.filter(QString("*.").append(extension));

    return filteredList;
}

const QString createNameFilter(const QString& title, const QStringList& permittedFormats)
{
    QString nameFilter;

    nameFilter.append(title);

    nameFilter.append(" (");
    for(auto format : permittedFormats)
    {
        nameFilter.append("*.").append(format).append(" ");
    }
    nameFilter.append(")");

    return nameFilter;
}

}
