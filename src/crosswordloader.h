#ifndef CROSSWORDLOADER_H
#define CROSSWORDLOADER_H

#include "crosswordstate.h"

namespace Crossword
{

// Base class for loading crosswords.
class CrosswordLoader
{
public:
    CrosswordLoader();

    // Importers implement functionality for loading the crossword file
    // An importer should not make any changes to the crossword state if there is a failure
    // Takes a full filepath to load from and crossword state to write populate
    virtual bool load(const QString& filepath, CrosswordState& state) const = 0;
};
}

#endif // CROSSWORDLOADER_H
