#include "xwcloader.h"
#include "xwccommon.h"
#include "formatscommon.h"

#include "crosswordclue.h"
#include "crossworditem.h"
#include <QColor>

using namespace Crossword;
using namespace Crossword::Formats;
using namespace VectorMath;

XWCLoader::XWCLoader() : CrosswordLoader()
{
}

bool XWCLoader::load(const QString& filepath, CrosswordState& puzzle) const
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

    success = loadSolveGrid(puzzle, data);
    if(!success)
    {
        return false;
    }

    return true;
}

bool XWCLoader::loadMetadata(CrosswordState& puzzle, QStringList& lines) const
{
    // Format version and name
    puzzle.m_FileFormat.m_Extension = Crossword::Formats::XWC101.first;
    puzzle.m_FileFormat.m_Version = Crossword::Formats::VERSION_UNKNOWN;

    // Line 1: Version number followed by Author name
    puzzle.m_Metadata.m_Authors = lines.takeFirst();

    // Line 2: Crossword Title
    puzzle.m_Metadata.m_Title = lines.takeFirst();

    // Line 3: Crossword Mode
    auto validModes = XWC::Common::getModes();
    QString mode = lines.takeFirst();
    // If the puzzle mode is invalid or has been read incorrectly then give up
    if(!validModes.contains(mode))
    {
        return false;
    }

    puzzle.m_Metadata.m_Type = mode;

    if(puzzle.m_Metadata.m_Authors.isNull() || puzzle.m_Metadata.m_Title.isNull() || puzzle.m_Metadata.m_Type.isNull())
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
    puzzle.m_GridState.m_Dimensions.z(1); // 1 grid layer

    return true;
}

bool XWCLoader::loadGrid(CrosswordState& puzzle, QStringList& lines) const
{
    // Next lines contain the Solution grid - one line for each row of the grid
    // Lower case letters are used for the solution words, with a '1' for each black square.
    // If all the words have not yet been entered, there will be a '0' (zero) for each empty white square.
    // This depends on the Mode.
    auto modes = XWC::Common::getModes();
    auto mode = modes.find(puzzle.m_Metadata.m_Type).value();

    readGrid(puzzle, lines);

    // If the Mode is Skeleton, then there will only be zeroes and ones in the grid.
    if(XWC::Modes::SKELETON == mode)
    {

    }
    // If the Mode is Solution, some or all of the zeroes will have been replaced by lower case letters.
    else if(XWC::Modes::SOLUTION == mode)
    {

    }
    // If the Mode is Clue, all of the solution words will be present together with '1's representing the black squares.
    else if(XWC::Modes::CLUE == mode)
    {

    }

    return true;
}

bool XWCLoader::readGrid(CrosswordState& puzzle, QStringList& lines) const
{
    // Grid size
    int gridX = puzzle.m_GridState.m_Dimensions.x();
    int gridY = puzzle.m_GridState.m_Dimensions.y();

    // Loop over the grid line by line
    for(int y = 0; y < gridY; y++)
    {
        QString currentLine = lines.takeFirst();

        for(int x = 0; x < gridX; x++)
        {
            QChar currentCharacter = currentLine.at(x);
            Q_ASSERT(currentCharacter.isLetterOrNumber());

            // Lower case letters are used for the solution words, with a '1' for each black square.
            if(currentCharacter == XWC::Common::blackSquare)
            {
                puzzle.m_GridState.m_Grid.push_back(std::make_tuple(Vec3i(x, y, 0), CrosswordItem(QString(""), QColor(Qt::black))));
            }
            // If all the words have not yet been entered, there will be a '0' (zero) for each empty white square.
            else
            {
                puzzle.m_GridState.m_Grid.push_back(std::make_tuple(Vec3i(x, y, 0), CrosswordItem(QString(currentCharacter), QColor(Qt::white))));
            }
        }
    }

    return true;
}

bool XWCLoader::loadCluesForDirection(CrosswordState& puzzle, QStringList& lines, Crossword::Formats::Direction direction) const
{
    bool ok;
    int numClues = lines.takeFirst().toInt(&ok);
    if(!ok)
    {
        return false; // Conversion failed
    }

    for(int i = 0; i < numClues; i++)
    {
        QStringList currentClue = lines.takeFirst().split(XWC::Common::clueAttributeSeparator, QString::SplitBehavior::SkipEmptyParts);

        // Each clue line has the following format: [R-J = Right-justified. L-J = Left justified.]
        // Chars 1-3 R-J Clue number
        QString clueNumber = currentClue.takeFirst();

        // Char 4 Vertical bar
        // Chars 5-6 R-J Row number of the first letter of the solution word in the grid.
        int row = currentClue.takeFirst().toInt(&ok);

        if(!ok)
        {
            return false;
        }

        // Char 7 Vertical bar
        // Chars 8-9 R-J Column number of the first letter of the solution word in the grid.
        int column = currentClue.takeFirst().toInt(&ok);

        if(!ok)
        {
            return false;
        }

        // Check that the row or column does not go past the size of the grid
        if(row > puzzle.m_GridState.m_Dimensions.x() || column > puzzle.m_GridState.m_Dimensions.y())
        {
            return false;
        }

        // Char 10 Vertical bar
        // Chars 11-12 R-J Number of letters in the solution word.
        int solutionLength = currentClue.takeFirst().toInt(&ok);

        if(!ok)
        {
            return false;
        }

        // Char 13 Vertical bar
        // Next characters contain the uppercase solution word L-J followed by a vertical bar.
        QString solution = currentClue.takeFirst();

        // If the clue has been defined, the words of the clue optionally followed by the word length in parentheses.
        QString clueWords;

        if(!currentClue.isEmpty())
        {
            clueWords = currentClue.takeFirst();
        }

        // Get the positions of the letters in the grid
        VectorMath::Vec3i startingPosition(row, column, 0);
        std::vector<VectorMath::Vec3i> letterPositions;

        if(Formats::Direction::ACROSS == direction)
        {
            for(int i = 0; i < solutionLength; i++)
            {
                letterPositions.push_back(startingPosition + VectorMath::Vec3i(i, 0, 0));
            }
        }
        else if(Formats::Direction::DOWN == direction)
        {
            for(int i = 0; i < solutionLength; i++)
            {
                letterPositions.push_back(startingPosition + VectorMath::Vec3i(0, i, 0));
            }
        }
        else
        {
            return false;
        }

        // Convert the direction enum to a string
        auto directions = Formats::Common::getDirections();
        QString directionString = directions.key(direction);

        CrosswordClue clue(clueNumber, "", solution, clueWords, directionString, "", letterPositions);

        Q_ASSERT(clue.getDirection() == directionString);

        // Add the clue to the puzzle
        puzzle.m_ClueState.m_Clues.push_back(clue);
    }

    return true;
}

bool XWCLoader::loadClues(CrosswordState& puzzle, QStringList& lines) const
{
    // The first line after the solution grid contains the number of Across clues.
    // This means that the next lines contain a number of Across clues, one per line.
    if(!loadCluesForDirection(puzzle, lines, Formats::Direction::ACROSS))
    {
        return false;
    }

    // Immediately following the Across clues is the number of Down clues.
    // Each clue line has a format identical to that of the Across clues.
    if(!loadCluesForDirection(puzzle, lines, Formats::Direction::DOWN))
    {
        return false;
    }

    return true;
}

bool XWCLoader::loadSolveGrid(CrosswordState &puzzle, QStringList &lines) const
{
    Q_UNUSED(lines);
    Q_UNUSED(puzzle);

    auto modes = XWC::Common::getModes();
    auto mode = modes.find(puzzle.m_Metadata.m_Type).value();

    // If the Mode is Solve, the grid will look the same as for Clue mode, but there will be an additional Solve grid at the end of the file.
    if(XWC::Modes::SOLVE == mode)
    {
        // If the Mode is Solve, immediately following the Down clues is the Solve grid,
        // one row for each row of the crossword. It is similar to the Solution grid
        // except that the solved words are in upper case characters.
    }

    return true;
}
