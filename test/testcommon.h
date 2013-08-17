#ifndef TESTCOMMON_H
#define TESTCOMMON_H

#include <QString>

#include "utilities.h"

namespace Tests
{

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

}

#endif // TESTCOMMON_H