#ifndef XWC3DLOADER_H
#define XWC3DLOADER_H

#include "crosswordformat.h"
#include "crosswordloader.h"
#include "formatscommon.h"

namespace Crossword
{

namespace Formats
{

class XWC3DLoader : public CrosswordLoader
{
public:
    XWC3DLoader();

    virtual bool load(const QString& filepath, CrosswordState& puzzle) const override;

private:
    bool loadMetadata(CrosswordState& puzzle, QStringList& lines) const;
    bool loadGridHighlights(CrosswordState& puzzle, QStringList& lines) const;
    bool loadGrid(CrosswordState& puzzle, QStringList& lines) const;
    bool loadClues(CrosswordState& puzzle, QStringList& lines) const;

    bool readGrid(CrosswordState& puzzle, QStringList& lines, std::pair<QString, QString> format) const; // loadGrid helper method
    bool loadCluesForDirection(CrosswordState& puzzle, QStringList& lines, Formats::Directions direction) const; // loadClues helper method

    const std::vector<VectorMath::Vec3i> loadLetterPositionsForDirection(Formats::Directions direction) const; // Snaking clues
    const std::vector<VectorMath::Vec3i> loadLetterPositionsForDirection(Formats::Directions direction, VectorMath::Vec3i startPosition) const; // All other clues
};

}
}

#endif // XWC3DLOADER_H
