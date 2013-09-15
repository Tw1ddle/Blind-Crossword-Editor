#ifndef XWCLOADER_H
#define XWCLOADER_H

#include "crosswordloader.h"
#include "crosswordformat.h"
#include "formatscommon.h"

namespace Crossword
{

namespace Formats
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

    bool readGrid(CrosswordState& puzzle, QStringList& lines) const; // loadGrid helper method
    bool loadCluesForDirection(CrosswordState& puzzle, QStringList& lines, Crossword::Formats::Direction direction) const; // loadClues helper method
};

}
}

#endif // XWCLOADER_H
