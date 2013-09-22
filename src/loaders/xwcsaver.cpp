#include "xwcsaver.h"

#include "crosswordstatistics.h"
#include "xwccommon.h"
#include "utilities.h"

#include <QDebug>

namespace Crossword
{

namespace Formats
{

XWCSaver::XWCSaver() : CrosswordSaver()
{
}

QStringList XWCSaver::save(const CrosswordState& state) const
{
    QStringList lines;

    if(!saveMetadata(state, lines))
    {
        return QStringList();
    }

    if(!saveGrid(state, lines))
    {
        return QStringList();
    }

    if(!saveClues(state, lines))
    {
        return QStringList();
    }

    if(!saveSolveGrid(state, lines))
    {
        return QStringList();
    }

    return lines;
}

bool XWCSaver::saveMetadata(const CrosswordState& state, QStringList& lines) const
{
    const auto& metadata = state.m_Metadata;

    // Line 1: Version number followed by Author name.
    if(!metadata.m_Authors.contains(XWC::Common::TXWordGridVersionIdentifier))
    {
        // This layout adopted from The Guardian Quick Crossword 12412.
        lines += XWC::Common::TXWordGrid3VersionIdentifier + " * " + metadata.m_Authors;
    }
    else
    {
        lines += metadata.m_Authors;
    }

    // Line 2: Crossword Title
    lines += metadata.m_Title;

    // Line 3: Crossword Mode: Skeleton, Solution, Clue, Solve
    lines += metadata.m_Type;


    const auto& grid = state.m_GridState;

    // Line 4: Number of rows in the crossword grid
    lines += QString::number(grid.m_Dimensions.x());
    // Line 5: Number of columns in the crossword grid
    lines += QString::number(grid.m_Dimensions.y());

    return true;
}

bool XWCSaver::saveGrid(const CrosswordState& state, QStringList& lines) const
{
    const auto& grid = state.m_GridState;

    const int gridX = grid.m_Dimensions.x();
    const int gridY = grid.m_Dimensions.y();

    // Next lines write the Solution grid
    for(int y = 0; y < gridY; y++)
    {
        QString currentLine;
        for(int x = 0; x < gridX; x++)
        {
            // Get the character at the current index and convert it to lower case (lower case characters only in solution grid)
            QString currentCharacter = std::get<CrosswordState::GridState::ITEM>(grid.m_Grid.at(x + (y * gridY))).getText().toLower();

            if(currentCharacter.isEmpty())
            {
                // Empty, so a white square
                currentCharacter = XWC::Common::whiteSquare;
            }

            currentLine += currentCharacter;
        }

        lines += currentLine;
    }

    return true;
}

bool XWCSaver::saveClues(const CrosswordState& state, QStringList& lines) const
{
    // The first line after the solution grid contains the number of Across clues.
    if(!saveCluesForDirection(state, lines, Direction::ACROSS))
    {
        return false;
    }

    // Followed by Down clues
    if(!saveCluesForDirection(state, lines, Direction::DOWN))
    {
        return false;
    }

    return true;
}

bool XWCSaver::saveCluesForDirection(const CrosswordState& state, QStringList& lines, Crossword::Formats::Direction direction) const
{
    // Convert the direction enum to a string
    auto directions = Formats::Common::getDirections();

    QString directionString = directions.key(direction);
    QString numInDirection = Editor::numCluesForDirection(state, directionString);
    lines += numInDirection;

    const auto& clues = state.m_ClueState.m_Clues;

    for(const auto& clue : clues)
    {
        if(clue.getDirection() == directionString)
        {
            QString line;

            // Chars 1-3 R-J Clue number
            // Char 4 Vertical bar
            line += clue.getNumber().rightJustified(3);
            line += XWC::Common::clueAttributeSeparator;

            // Chars 5-6 R-J Row number of the first letter of the solution word in the grid.
            // Char 7 Vertical bar
            line += QString::number(clue.getLetterPositions().at(0).x()).rightJustified(2);
            line += XWC::Common::clueAttributeSeparator;

            // Chars 8-9 R-J Column number of the first letter of the solution word in the grid.
            // Char 10 Vertical bar
            line += QString::number(clue.getLetterPositions().at(0).y()).rightJustified(2);
            line += XWC::Common::clueAttributeSeparator;

            // Chars 11-12 R-J Number of letters in the solution word.
            // Char 13 Vertical bar
            line += QString::number(clue.getLetterPositions().size()).rightJustified(2);
            line += XWC::Common::clueAttributeSeparator;

            // Next characters contain the uppercase solution word L-J followed by a vertical bar.
            line += clue.getSolution().toUpper();
            line += XWC::Common::clueAttributeSeparator;

            // The clue text itself
            line += clue.getClue();

            lines += line;
        }
    }

    return true;
}

bool XWCSaver::saveSolveGrid(const CrosswordState& state, QStringList& lines) const
{
    // If the Mode is Solve, immediately following the Down clues is the Solve grid,
    // one row for each row of the crossword.
    // It is similar to the Solution grid except that the solved words are in upper case characters.
    const auto& metadata = state.m_Metadata;
    auto modes = XWC::Common::getModes();
    auto mode = modes.find(metadata.m_Type).value();

    // TODO replace this with a loop that inserts the current guesses/solutions
    // from the clues, rather than just an uppercase grid
    QStringList solveGrid;
    if(mode == XWC::Modes::SOLVE)
    {
        saveGrid(state, solveGrid);

        for(auto& line : solveGrid)
        {
            for(auto& letter : line)
            {
                if(letter.isLetter())
                {
                    letter = letter.toUpper();
                }
            }
        }

        lines += solveGrid;
    }

    return true;
}

}
}
