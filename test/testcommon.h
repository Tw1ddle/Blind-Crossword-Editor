#ifndef TESTCOMMON_H
#define TESTCOMMON_H

#include <QString>

#include "utilities.h"

namespace Tests
{

QStringList getTestDataFilepaths(QString dirPath);

QString getFilenameForFilepath(QString filePath);

// Get standard puzzle path
inline QString getRegularCrosswordTestPath()
{
    auto path = Utilities::getApplicationDirPath().append("/test/data/crosswords/regular/");

    return path;
}

// Get unusual puzzle path
inline QString getUnusualCrosswordTestPath()
{
    auto path = Utilities::getApplicationDirPath().append("/test/data/crosswords/unusual/");

    return path;
}

// Get broken puzzle path
inline QString getBrokenCrosswordTestPath()
{
    auto path = Utilities::getApplicationDirPath().append("/test/data/crosswords/broken/");

    return path;
}

// Invalid puzzles
inline QString getInvalidCrosswordTestPath()
{
    auto path = Utilities::getApplicationDirPath().append("/test/data/crosswords/invalid/");

    return path;
}

// Directory for saving puzzles in during the
inline QString getSaveTestDirectoryPath()
{
    auto path = Utilities::getApplicationDirPath().append("/test/savetests/");

    return path;
}

}

#endif // TESTCOMMON_H
