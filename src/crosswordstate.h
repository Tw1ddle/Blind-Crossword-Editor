#ifndef CROSSWORDSTATE_H
#define CROSSWORDSTATE_H

#include <QString>

#include <memory>
#include <vector>

namespace Crossword
{

// Encapsulates the state of a crossword puzzle
class CrosswordState
{
public:
    CrosswordState();

private:
    // Technical metadata
    // File format
    struct FileFormat
    {
        QString m_Name; // Name of the file format
        QString m_Version; // Which revision of the format
        QString m_WrittenBy; // Which tool wrote the file
    };

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

    // State of the grids
    struct GridState
    {
        //std::unique_ptr<GridData> m_Grid;
    };

    // Clues inside the grid
    // Background images and picture clues
    struct ClueState
    {
        //std::vector<std::unique_ptr<Clue>> m_Clues;
        //std::vector<std::unique_ptr<Image>> m_Images;
    };
};
}

#endif // CROSSWORDSTATE_H
