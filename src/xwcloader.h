#ifndef XWCLOADER_H
#define XWCLOADER_H

#include "crosswordloader.h"
#include "crosswordformat.h"

namespace Crossword
{

// Loads Spoonbill Crossword Compiler (.xwc) puzzle format files
class XWCLoader : public CrosswordLoader
{
public:
    XWCLoader();

    virtual bool load(const QString& filepath, CrosswordState& puzzle) const override;

private:
    bool loadMetadata(CrosswordState& puzzle, QStringList& lines) const;
    bool loadGrid(CrosswordState& puzzle, QStringList& lines) const;
    bool loadClues(CrosswordState& puzzle, QStringList& lines) const;
    bool loadSolveGrid(CrosswordState& puzzle, QStringList& lines) const;
};

}

#endif // XWCLOADER_H
