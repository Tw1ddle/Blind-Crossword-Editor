#include "xwc3dloader.h"

#include "crosswordformat.h"
#include "xwc3dcommon.h"
#include "crosswordclue.h"

using namespace Crossword;
using namespace Crossword::Formats;
using namespace VectorMath;

XWC3DLoader::XWC3DLoader()
{
}

bool Crossword::Formats::XWC3DLoader::load(const QString& filepath, Crossword::CrosswordState& puzzle) const
{
    QStringList data = readFile(filepath, puzzle);

    // Empty file or failed to read
    bool success = !data.empty();
    if(!success)
    {
        return false;
    }

    success = loadMetadata(puzzle, data);
    if(!success)
    {
        return false;
    }

    success = loadGridHighlights(puzzle, data);
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

bool XWC3DLoader::loadMetadata(CrosswordState& puzzle, QStringList& lines) const
{
    // File metadata. All lines are mandatory for this version of the format.

    // Line 1: Format type
    puzzle.m_FileFormat.m_Extension = lines.takeFirst();

    // Line 2: Format version
    puzzle.m_FileFormat.m_Version = lines.takeFirst();

    if(puzzle.m_FileFormat.m_Extension.isNull() || puzzle.m_FileFormat.m_Extension.isNull())
    {
        return false;
    }

    // Line 3: Crossword title
    puzzle.m_Metadata.m_Title = lines.takeFirst();

    // Line 4: Crossword author(s)
    puzzle.m_Metadata.m_Authors = lines.takeFirst();

    // Line 5: Puzzle mode or type
    auto validModes = XWC3D::Common::getModes();
    QString mode = lines.takeFirst();
    if(!validModes.contains(mode))
    {
        return false;
    }
    puzzle.m_Metadata.m_Type = mode;

    // Line 6: Puzzle notes - information such as what any highlights or special features mark, hints etc.
    puzzle.m_Metadata.m_Notes = lines.takeFirst();

    if(puzzle.m_Metadata.m_Authors.isNull() || puzzle.m_Metadata.m_Title.isNull() || puzzle.m_Metadata.m_Type.isNull() || puzzle.m_Metadata.m_Notes.isNull())
    {
        return false;
    }

    // Line 7: The filename of a background image.
    // JPG is supported in this application
    puzzle.m_DataSources.m_BackgroundImagePath = lines.takeFirst();

    // Line 8-11: X, Y, Z grid dimensions
    int gridX = lines.takeFirst().toUInt();
    int gridY = lines.takeFirst().toUInt();
    int gridZ = lines.takeFirst().toUInt();

    if(gridX <= 0 || gridY <= 0 || gridZ <= 0)
    {
        return false;
    }

    puzzle.m_GridState.m_Dimensions.x(gridX);
    puzzle.m_GridState.m_Dimensions.y(gridY);
    puzzle.m_GridState.m_Dimensions.z(gridZ);

    return true;
}

bool XWC3DLoader::loadGridHighlights(CrosswordState& puzzle, QStringList& lines) const
{
    // Line 12: grid highlights
    // Structure is X,Y,Z,COLOUR
    QStringList highlights = lines.takeFirst().split(XWC3D::Common::highlightAttributeSeparator);

    while(!highlights.empty())
    {
        QStringList currentHighlight = highlights.takeFirst().split(XWC3D::Common::subattributeSeparator);

        const int numSubattributes = 4;
        if(currentHighlight.size() == numSubattributes)
        {
            int x = currentHighlight.takeFirst().toInt() - 1;
            int y = currentHighlight.takeFirst().toInt() - 1;
            int z = currentHighlight.takeFirst().toInt() - 1;

            QString colourName = currentHighlight.takeFirst();

            // TODO apply the highlights to the grid
            puzzle.m_GridState;

            Q_UNUSED(x);
            Q_UNUSED(y);
            Q_UNUSED(z);
            Q_UNUSED(colourName);
        }
    }

    return true;
}

bool XWC3DLoader::loadGrid(CrosswordState& puzzle, QStringList& lines) const
{
    // Next lines contain the Solution grid - one line for each row of the grid
    // Lower case letters are used for the solution words, with a '1' for each black square.
    // If all the words have not yet been entered, there will be a '0' (zero) for each empty white square.

    // Check that the file format is recognized
    auto formats = Formats::get3DFormats();
    auto extension = puzzle.m_FileFormat.m_Extension;
    if(!formats.contains(extension))
    {
        return false;
    }

    // There are two possible grid layouts - rectangular grids and combination lock grids
    // Rectangular grids
    auto rectangularGridFormat = Crossword::Formats::XWC3D100;
    if(rectangularGridFormat.first == extension)
    {
        return readGrid(puzzle, lines, rectangularGridFormat);
    }

    // Combination lock grids
    auto combinationGridFormat = Crossword::Formats::XWC3DR100;
    if(combinationGridFormat.first == extension)
    {
        return readGrid(puzzle, lines, combinationGridFormat);
    }

    return false;
}

bool XWC3DLoader::readGrid(CrosswordState& puzzle, QStringList& lines, std::pair<QString, QString> format) const
{
    const VectorMath::Vec3i dimensions = puzzle.m_GridState.m_Dimensions;

    if(format == Crossword::Formats::XWC3D100) // Rectangular grids
    {
        // Loop over the grids line by line
        for(int z = 0; z < dimensions.z(); z++)
        {
            for(int y = 0; y < dimensions.y(); y++)
            {
                QString currentLine = lines.takeFirst();

                for(int x = 0; x < dimensions.x(); x++)
                {
                    QChar currentCharacter = currentLine.at(x);

                    if(currentCharacter == XWC3D::Common::blackSquare)
                    {
                        puzzle.m_GridState.m_Grid.push_back(std::make_pair(Vec3i(x, y, z), CrosswordItem(QString(""), QColor(Qt::black))));
                    }
                    else
                    {
                        puzzle.m_GridState.m_Grid.push_back(std::make_pair(Vec3i(x, y, z), CrosswordItem(QString(currentCharacter), QColor(Qt::white))));
                    }
                }
            }
        }

        return true;
    }

    if(format == Crossword::Formats::XWC3DR100) // Combination lock grids
    {
        for(int z = 0; z < dimensions.z(); z++)
        {
            for(int y = 0; y < dimensions.y(); y++)
            {
                QString currentLine = lines.takeFirst();

                if(y == 0) // Disc hub
                {
                    for(int x = 0; x < dimensions.x(); x++)
                    {
                        QChar currentCharacter = currentLine.at(0);

                        if(currentLine.at(0) == XWC3D::Common::blackSquare)
                        {
                            puzzle.m_GridState.m_Grid.push_back(
                                        std::make_pair(Vec3i(x, y, z), CrosswordItem(QString(""), QColor(Qt::black))));
                        }
                        else
                        {
                            puzzle.m_GridState.m_Grid.push_back(
                                        std::make_pair(Vec3i(x, y, z), CrosswordItem(QString(currentCharacter), QColor(Qt::black))));
                        }
                    }
                }
                else
                {
                    for(int x = 0; x < dimensions.x(); x++)
                    {
                        QChar currentCharacter = currentLine.at(x);

                        if(currentLine.at(z) == XWC3D::Common::blackSquare)
                        {
                            puzzle.m_GridState.m_Grid.push_back(
                                        std::make_pair(Vec3i(x, y, z), CrosswordItem(QString(""), QColor(Qt::black))));
                        }
                        else
                        {
                            puzzle.m_GridState.m_Grid.push_back(
                                        std::make_pair(Vec3i(x, y, z), CrosswordItem(QString(currentCharacter), QColor(Qt::white))));
                        }
                    }
                }
            }
        }

        return true;
    }

    return false;
}

bool XWC3DLoader::loadClues(CrosswordState& puzzle, QStringList& lines) const
{
    // The first line after the solution grid contains the type of clue coming next
    // The following line lists the number of these clues

    // For rectangular grids, the clues are listed in order: Across, Backwards, Away, Towards, Down, Up, Snaking.
    // If there are none of a particular clue, the number of clues listed is 0.

    while(!lines.empty())
    {
        QString direction = lines.takeFirst();

        // Check it's a valid direction
        auto validDirections = Crossword::Formats::Common::getDirections();
        if(!validDirections.contains(direction))
        {
            return false;
        }

        auto directionEnum = validDirections.find(direction).value();

        bool success = loadCluesForDirection(puzzle, lines, directionEnum);

        if(!success)
        {
            return false;
        }
    }

    return true;
}

bool XWC3DLoader::loadCluesForDirection(CrosswordState& puzzle, QStringList& lines, Crossword::Formats::Directions direction) const
{
    // Get the number of clues for the given direction
    bool ok;
    int numClues = lines.takeFirst().toInt(&ok);
    if(!ok)
    {
        return false;
    }

    // TODO Fetch the guess for the clue within the grid
    for(int i = 0; i < numClues; i++)
    {
        QStringList currentClue = lines.takeFirst().split(XWC3D::Common::clueAttributeSeparator);

        // The unique identifier for the clue
        QString identifier = currentClue.takeFirst();
        Q_UNUSED(identifier);

        // The clue number as shown to an end user
        QString number = currentClue.takeFirst();

        // The letter positions of the clue guess
        std::vector<Vec3i> letterPositions;
        if(direction != Formats::Directions::SNAKING)
        {
            // The starting coordinate of the clue
            QStringList startPositionList = currentClue.takeFirst().split(XWC3D::Common::subattributeSeparator);
            int gridX = startPositionList.takeFirst().toInt() - 1;
            int gridY = startPositionList.takeFirst().toInt() - 1;
            int gridZ = startPositionList.takeFirst().toInt() - 1;
            VectorMath::Vec3i startPosition(gridX, gridY, gridZ);

            letterPositions = loadLetterPositionsForDirection(direction, startPosition);
        }
        else
        {
            letterPositions = loadLetterPositionsForDirection(direction);
        }

        // TODO add assertion
        QString length = currentClue.takeFirst();
        Q_UNUSED(length);

        QString guessText = currentClue.takeFirst();

        QString clueText = currentClue.takeFirst();

        // TODO pass this in
        QString clueComponentLengths = currentClue.takeFirst();
        Q_UNUSED(clueComponentLengths);

        // Convert the direction enum to a string
        auto directions = Formats::Common::getDirections();
        QString directionString = directions.key(direction);

        CrosswordClue clue(number, guessText, "", clueText, directionString, letterPositions);

        puzzle.m_ClueState.m_Clues.push_back(clue);
    }

    return true;
}


const std::vector<Vec3i> XWC3DLoader::loadLetterPositionsForDirection(Directions direction, Vec3i startPosition) const
{
    // TODO
    Q_UNUSED(direction);
    Q_UNUSED(startPosition);

    return std::vector<Vec3i>();
}

const std::vector<Vec3i> XWC3DLoader::loadLetterPositionsForDirection(Directions direction) const
{
    Q_UNUSED(direction);

    return std::vector<Vec3i>();
}
