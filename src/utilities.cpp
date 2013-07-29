#include "utilities.h"

#include <QTextStream>

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

}
