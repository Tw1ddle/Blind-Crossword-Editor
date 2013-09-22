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

    return load(data, puzzle);
}

bool AcrossLiteTextLoader::load(const QStringList& data, CrosswordState& puzzle) const
{
    QStringList lines = data;

    bool success = false;

    success = loadMetadata(puzzle, lines);
    if(!success)
    {
        return false;
    }

    success = loadGrid(puzzle, lines);
    if(!success)
    {
        return false;
    }

    success = loadClues(puzzle, lines);
    if(!success)
    {
        return false;
    }

    return true;
}

CrosswordState AcrossLiteTextLoader::load(const QStringList& data) const
{
    CrosswordState state;

    load(data, state);

    return state;
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
