#include "acrosslitetextloader.h"
#include "formatscommon.h"

#include "crosswordclue.h"
#include "crossworditem.h"
#include <QColor>

using namespace VectorMath;

// TODO implement this

namespace Crossword
{

namespace Formats
{

AcrossLiteTextLoader::AcrossLiteTextLoader()
{

}

bool AcrossLiteTextLoader::load(const QString& filepath, CrosswordState& puzzle) const
{
    QStringList data = readFile(filepath, puzzle);

    // Empty file or failed to read
    bool success = !data.empty();
    if(!success)
    {
        return false;
    }

    // Datasources
    puzzle.m_DataSources.m_PuzzleFilePath = filepath;

    success = loadMetadata(puzzle, data);
    if(!success)
    {
        return false;
    }

    success = loadGrid(puzzle, data);
    if(!success)
    {
        return false;
    }

    success = loadClues(puzzle, data);
    if(!success)
    {
        return false;
    }

    return true;
}

bool AcrossLiteTextLoader::loadMetadata(CrosswordState& puzzle, QStringList& lines) const
{
    Q_UNUSED(lines);
    Q_UNUSED(puzzle);

    return true;
}

bool AcrossLiteTextLoader::loadGrid(CrosswordState& puzzle, QStringList& lines) const
{
    Q_UNUSED(lines);
    Q_UNUSED(puzzle);

    return true;
}

bool AcrossLiteTextLoader::readGrid(CrosswordState& puzzle, QStringList& lines) const
{
    Q_UNUSED(lines);
    Q_UNUSED(puzzle);

    return true;
}

bool AcrossLiteTextLoader::loadCluesForDirection(CrosswordState& puzzle, QStringList& lines, Crossword::Formats::Direction direction) const
{
    Q_UNUSED(lines);
    Q_UNUSED(puzzle);
    Q_UNUSED(direction);

    return true;
}

bool AcrossLiteTextLoader::loadClues(CrosswordState& puzzle, QStringList& lines) const
{
    Q_UNUSED(lines);
    Q_UNUSED(puzzle);

    return true;
}

}
}
