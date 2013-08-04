#include "utilities.h"

#include <QTextStream>
#include <QDesktopServices>
#include <QUrl>

namespace Utilities
{

bool readFile(const QString& path, QStringList& text)
{
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

}
