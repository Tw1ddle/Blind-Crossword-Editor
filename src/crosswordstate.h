#ifndef CROSSWORDSTATE_H
#define CROSSWORDSTATE_H

#include <QString>

#include <memory>
#include <vector>

#include "crosswordclue.h"
#include "vectormath.h"

namespace Crossword
{

// Encapsulates the state of a crossword puzzle
class CrosswordState
{
public:
    CrosswordState();

    // Technical metadata
    // File format
    struct FileFormat
    {
        QString m_Name; // Name of the file format
        QString m_Version; // Which revision of the format
    };
    FileFormat m_FileFormat;

    // User metadata
    QString m_Title;
    QString m_Authors;
    QString m_Type; // Normal, cryptic etc
    QString m_Notes; // Any additional information

    // Data paths
    struct DataSources
    {
        QString m_PuzzleFilePath; // Path to the actual puzzle file that was loaded up (if any)
        QString m_BackgroundImagePath; // Path to the background image loaded for this puzzle
    };
    DataSources m_DataSources;

    // State of the grids
    struct GridState
    {
        VectorMath::Vec3i m_Dimensions;
        //std::unique_ptr<GridData> m_Grid;
    };
    GridState m_GridState;

    // Clues inside the grid
    // Background images and picture clues
    struct ClueState
    {
        std::vector<std::unique_ptr<CrosswordClue>> m_Clues;
        //std::vector<std::unique_ptr<Image>> m_Images;
    };
    ClueState m_ClueState;
};
}

#endif // CROSSWORDSTATE_H
