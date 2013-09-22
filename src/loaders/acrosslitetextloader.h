#ifndef ACROSSLITETEXTLOADER_H
#define ACROSSLITETEXTLOADER_H

#include "crosswordloader.h"
#include "crosswordformat.h"
#include "formatscommon.h"

namespace Crossword
{

namespace Formats
{

// Loads Across Lite Text (.txt) puzzle format files
// TODO is the correct file format extension indeed .txt?
class AcrossLiteTextLoader : public CrosswordLoader
{
public:
    AcrossLiteTextLoader();

    virtual bool load(const QString& filepath, CrosswordState& puzzle) const override;
    virtual bool load(const QStringList& data, CrosswordState& puzzle) const override;

    virtual CrosswordState load(const QStringList& data) const override;

private:
    bool loadMetadata(CrosswordState& puzzle, QStringList& lines) const;
    bool loadGrid(CrosswordState& puzzle, QStringList& lines) const;
    bool loadClues(CrosswordState& puzzle, QStringList& lines) const;

    bool readGrid(CrosswordState& puzzle, QStringList& lines) const; // loadGrid helper method
    bool loadCluesForDirection(CrosswordState& puzzle, QStringList& lines, Crossword::Formats::Direction direction) const; // loadClues helper method
};

}
}

#endif // ACROSSLITETEXTLOADER_H
