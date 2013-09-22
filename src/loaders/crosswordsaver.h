#ifndef CROSSWORDSAVER_H
#define CROSSWORDSAVER_H

#include "crosswordstate.h"

#include <QFile>

namespace Crossword
{

namespace Formats
{

// Base class for saving crosswords.
class CrosswordSaver
{
public:
    CrosswordSaver();
    virtual ~CrosswordSaver();

    // Exporters implement functionality for saving the crossword file
    // An exporter should clean up after itself if there is a failure while writing
    // Return an empty QStringList on failure
    virtual QStringList save(const CrosswordState& state) const = 0;
};

}

}

#endif // CROSSWORDSAVER_H
