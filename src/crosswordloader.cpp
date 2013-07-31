#include "crosswordloader.h"

#include "utilities.h"

namespace Crossword
{

namespace Formats
{

CrosswordLoader::CrosswordLoader()
{
}

QStringList CrosswordLoader::readFile(const QString& filepath, CrosswordState& state) const
{
    QStringList data;
    bool success = Utilities::readFile(filepath, data);

    // Read failed
    Q_ASSERT(success);

    if(success)
    {
        // Set the puzzle file location
        state.m_DataSources.m_PuzzleFilePath = filepath;
    }

    return data;
}

}

}
