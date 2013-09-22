#include "xwc3dsaver.h"
#include "xwc3dcommon.h"
#include "crosswordstatistics.h"

using namespace Crossword;
using namespace Crossword::Formats;

XWC3DSaver::XWC3DSaver()
{
}

QStringList XWC3DSaver::save(const CrosswordState& state) const
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

    return lines;
}

bool XWC3DSaver::saveMetadata(const CrosswordState& state, QStringList& lines) const
{
    // Metadata

    // Line 1: Format type
    lines += Formats::XWC3D100.first;

    // Line 2: Format version
    lines += Formats::XWC3D100.second;

    const auto& metadata = state.m_Metadata;

    // Line 3: Crossword title
    lines += metadata.m_Title;

    // Line 4: Crossword author(s)
    lines += metadata.m_Authors;

    // Line 5: Puzzle mode or type
    lines += metadata.m_Type;

    // Line 6: Puzzle notes - information such as what any highlights or special features mark, hints etc.
    lines += metadata.m_Notes;

    // Datasources
    const auto& dataSources = state.m_DataSources;

    // Line 7: The filename of a background image.
    // JPG is supported in this application
    lines += dataSources.m_BackgroundImagePath;

    return true;
}

bool XWC3DSaver::saveGrid(const CrosswordState& state, QStringList& lines) const
{
    // Grid
    const auto& grid = state.m_GridState;

    // Line 8-11: X, Y, Z grid dimensions
    lines += QString::number(grid.m_Dimensions.x());
    lines += QString::number(grid.m_Dimensions.y());
    lines += QString::number(grid.m_Dimensions.z());

    const int gridX = grid.m_Dimensions.x();
    const int gridY = grid.m_Dimensions.y();
    const int gridZ = grid.m_Dimensions.z();

    // Next lines write the Solution grid
    for(int z = 0; z < gridZ; z++)
    {
        for(int y = 0; y < gridY; y++)
        {
            QString currentLine;
            for(int x = 0; x < gridX; x++)
            {
                // Get the character at the current index

                // TODO use the appropriate math to find the grid coordinate
                // currentLine += std::get<CrosswordState::GridState::ITEM>(grid.m_Grid.at(x + (y * gridY))).getText();
            }
            lines += currentLine;
        }
    }

    // Optional grid highlights
    // TODO
    lines += "There is no highlight in this puzzle!";

    return true;
}

bool XWC3DSaver::saveClues(const CrosswordState& state, QStringList& lines) const
{
    // Clues

    if(!saveCluesForDirection(state, lines, Direction::ACROSS))
    {
        return false;
    }
    if(!saveCluesForDirection(state, lines, Direction::BACKWARDS))
    {
        return false;
    }
    if(!saveCluesForDirection(state, lines, Direction::AWAY))
    {
        return false;
    }
    if(!saveCluesForDirection(state, lines, Direction::TOWARDS))
    {
        return false;
    }
    if(!saveCluesForDirection(state, lines, Direction::DOWN))
    {
        return false;
    }
    if(!saveCluesForDirection(state, lines, Direction::UP))
    {
        return false;
    }
    if(!saveCluesForDirection(state, lines, Direction::SNAKING))
    {
        return false;
    }

    return true;
}

bool XWC3DSaver::saveCluesForDirection(const CrosswordState& state, QStringList& lines, Crossword::Formats::Direction direction) const
{
    // Convert the direction enum to a string
    auto directions = Formats::Common::getDirections();

    QString directionString = directions.key(direction);
    QString numInDirection = Editor::numCluesForDirection(state, directionString);
    lines += numInDirection;

    const auto& clues = state.m_ClueState.m_Clues;

    for(const auto& clue : clues)
    {
        // No empty clues allowed
        if(clue.getLetterPositions().size() <= 0)
        {
            return false;
        }

        if(clue.getDirection() == directionString)
        {
            QString line;

            // Unique identifier
            line += clue.getIdentifier();
            line += XWC3D::Common::clueAttributeSeparator;

            // Clue number
            line += clue.getNumber();
            line += XWC3D::Common::clueAttributeSeparator;

            // Letter positions
            auto& letterPositions = clue.getLetterPositions();

            // Number of letters in the solution word
            line += QString::number(letterPositions.size());
            line += XWC3D::Common::clueAttributeSeparator;

            if(direction != Direction::SNAKING)
            {
                // Row number of the first letter of the solution word in the grid.
                line += QString::number(letterPositions.at(0).x());
                line += XWC3D::Common::subAttributeSeparator;
                // Column number of the first letter of the solution word in the grid.
                line += QString::number(letterPositions.at(0).y());
                line += XWC3D::Common::subAttributeSeparator;
                // Grid depth number of the first letter of the solution word in the grid.
                line += QString::number(letterPositions.at(0).z());
                line += XWC3D::Common::clueAttributeSeparator;
            }
            else
            {
                // Snaking clues have all their letter coordinates listed
                for(size_t i = 0; i < clue.getLetterPositions().size(); i++)
                {
                    line += QString::number(letterPositions.at(i).x());
                    line += XWC3D::Common::subAttributeSeparator;
                    line += QString::number(letterPositions.at(i).y());
                    line += XWC3D::Common::subAttributeSeparator;
                    line += QString::number(letterPositions.at(i).z());
                    line += XWC3D::Common::clueAttributeSeparator;
                }
            }

            // Next characters contain the upper case solution word.
            line += clue.getSolution().toUpper();
            line += XWC3D::Common::clueAttributeSeparator;

            // The clue text itself.
            line += clue.getClue();
            line += XWC3D::Common::clueAttributeSeparator;

            // The solution word length breakdown e.g. (2,3)
            line += clue.getComponentLengths();

            lines += line;
        }
    }

    return true;
}
