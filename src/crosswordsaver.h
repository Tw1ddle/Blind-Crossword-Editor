#ifndef CROSSWORDSAVER_H
#define CROSSWORDSAVER_H

#include "crosswordstate.h"

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
    // Takes a full filepath to save to and a crossword state to read from
    virtual bool save(const QString& filepath, const CrosswordState& state) const = 0;
};

}

}

#endif // CROSSWORDSAVER_H
