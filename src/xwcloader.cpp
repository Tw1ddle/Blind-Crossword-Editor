#include "xwcloader.h"
#include "xwccommon.h"

#include "utilities.h"

#include "appinfo.h"

using namespace Crossword;

XWCLoader::XWCLoader() : CrosswordLoader()
{
}

bool XWCLoader::load(const QString& filepath, CrosswordState& puzzle) const
{
    QStringList data;
    bool success = Utilities::readFile(filepath, data);

    // Read failed
    if(!success)
    {
        return false;
    }

    // Empty file
    if(data.isEmpty())
    {
        return false;
    }

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

bool XWCLoader::loadMetadata(CrosswordState& puzzle, QStringList& lines) const
{
    // Format version and
    puzzle.m_FileFormat.m_Name = Crossword::Formats::XWC101.first;
    puzzle.m_FileFormat.m_Version = Crossword::Formats::VERSION_UNKNOWN;

    // Line 1: Version number followed by Author name
    puzzle.m_Authors = lines.takeFirst();

    // Line 2: Crossword Title
    puzzle.m_Title = lines.takeFirst();

    // Line 3: Crossword Mode
    QString mode = lines.takeFirst();

    puzzle.m_Type = mode;

    if(puzzle.m_Authors.isNull() || puzzle.m_Title.isNull() || puzzle.m_Type.isNull())
    {
        return false;
    }

    // Line 4: Number of rows in the crossword grid
    int gridX = lines.takeFirst().toUInt();

    // Line 5: Number of columns in the crossword grid
    int gridY = lines.takeFirst().toUInt();

    if(gridX <= 0 || gridY <= 0)
    {
        return false;
    }

    puzzle.m_GridState.m_Dimensions.x(gridX);
    puzzle.m_GridState.m_Dimensions.y(gridY);

    return true;
}

bool XWCLoader::loadGrid(CrosswordState& puzzle, QStringList& lines) const
{
    Q_UNUSED(lines);
    Q_UNUSED(puzzle);

    // Next lines contain the Solution grid - one line for each row of the grid
    // Lower case letters are used for the solution words, with a '1' for each black square.
    // If all the words have not yet been entered, there will be a '0' (zero) for each empty white square.
    // This depends on the Mode.
    // If the Mode is Skeleton, then there will only be zeroes and ones in the grid.
    // If the Mode is Solution, some or all of the zeroes will have been replaced by lower case letters.
    // If the Mode is Clue, all of the solution words will be present together with '1's representing the black squares.
    // If the Mode is Solve, the grid will look the same as for Clue mode, but there will be an additional Solve grid at the end of the file.

    return true;
}

bool XWCLoader::loadClues(CrosswordState& puzzle, QStringList& lines) const
{
    Q_UNUSED(lines);
    Q_UNUSED(puzzle);

    // The first line after the solution grid contains the number of Across clues.
    // For instance, in the example this is 23.
    // This means that the next 23 lines contain the twenty-three Across clues, one per line.

    // Each clue line has the following format: [R-J = Right-justified. L-J = Left justified.]
    // Chars 1-3 R-J Clue number
    // Char 4 Vertical bar
    // Chars 5-6 R-J Row number of the first letter of the solution word in the grid.
    // Char 7 Vertical bar
    // Chars 8-9 R-J Column number of the first letter of the solution word in the grid.
    // Char 10 Vertical bar
    // Chars 11-12 R-J Number of letters in the solution word.
    // Char 13 Vertical bar
    // Next characters contain the uppercase solution word L-J followed by a vertical bar.

    return true;
}

bool XWCLoader::loadSolveGrid(CrosswordState &puzzle, QStringList &lines) const
{
    Q_UNUSED(lines);
    Q_UNUSED(puzzle);

    // If the Mode is Solve, immediately following the Down clues is the Solve grid,
    // one row for each row of the crossword. It is similar to the Solution grid
    // except that the solved words are in upper case characters.

    return true;
}
