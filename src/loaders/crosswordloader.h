#ifndef CROSSWORDLOADER_H
#define CROSSWORDLOADER_H

#include "crosswordstate.h"

#include <QStringList>

namespace Crossword
{

namespace Formats
{

// Base class for loading crosswords.
class CrosswordLoader
{
public:
    CrosswordLoader();
    virtual ~CrosswordLoader();

    // Importers implement functionality for loading the crossword file
    // An importer should not make any changes to the crossword state if there is a failure
    // Takes a full filepath to load from and crossword state to write populate
    virtual bool load(const QString& filepath, CrosswordState& puzzle) const = 0;
    virtual bool load(const QStringList& data, CrosswordState& puzzle) const = 0;

    virtual CrosswordState load(const QStringList& data) const = 0;

protected:
    virtual QStringList readFile(const QString& filepath, CrosswordState& puzzle) const;
};

}

}

#endif // CROSSWORDLOADER_H
