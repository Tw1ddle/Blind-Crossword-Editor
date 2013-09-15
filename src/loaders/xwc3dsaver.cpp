#include "xwc3dsaver.h"
#include "xwc3dcommon.h"
#include "crosswordstatistics.h"

using namespace Crossword;
using namespace Crossword::Formats;

XWC3DSaver::XWC3DSaver()
{
}

bool XWC3DSaver::save(const QString& filepath, const CrosswordState& state) const
{
    QStringList lines;

    // Metadata

    // Line 1: Format type
    lines += Formats::XWC101.first;

    // Line 2: Format version
    lines += Formats::XWC101.second;

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

    // Clues


    Q_UNUSED(filepath);

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

    // TODO finish this and also worry about the

    for(const auto& clue : clues)
    {
        if(clue.getDirection() == directionString)
        {
            QString line;

            // Clue number
            line += clue.getNumber();
            line += XWC3D::Common::clueAttributeSeparator;

            // Row number of the first letter of the solution word in the grid.
            line += QString::number(clue.getLetterPositions().at(0).x());
            line += XWC3D::Common::clueAttributeSeparator;

            // Column number of the first letter of the solution word in the grid.
            line += QString::number(clue.getLetterPositions().at(0).y());
            line += XWC3D::Common::clueAttributeSeparator;

            // Grid depth number of the first letter of the solution word in the grid.

            // Number of letters in the solution word.
            line += QString::number(clue.getLetterPositions().size());
            line += XWC3D::Common::clueAttributeSeparator;

            // Next characters contain the solution word followed by a vertical bar.
            line += clue.getSolution().toUpper();
            line += XWC3D::Common::clueAttributeSeparator;

            // The clue text itself
            line += clue.getClue();

            lines += line;
        }
    }

    return true;
}
