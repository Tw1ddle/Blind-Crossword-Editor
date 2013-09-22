#include "testcommon.h"

#include <QDebug>

namespace Tests
{

QStringList getTestDataFilepaths(QString dirPath)
{
    QDir testDataDir(dirPath);

    auto files = Utilities::getFilepathsInDirectory(testDataDir);

    if(files.empty())
    {
        qWarning() << "No files found";
    }
    else
    {
        qDebug() << QString("%1 files found").arg(files.size());
    }

    return files;
}

QString getFilenameForFilepath(QString filePath)
{
    QFileInfo file(filePath);

    return file.fileName();
}

}
