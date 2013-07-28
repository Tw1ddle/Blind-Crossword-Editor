#ifndef CROSSWORDCLUE_H
#define CROSSWORDCLUE_H

#include <QString>
#include <vector>

#include "vectormath.h"

namespace Crossword
{

class CrosswordClue
{
public:
    enum class Direction
    {
        // 2D puzzles
        ACROSS, // Left to right
        BACKWARDS, // Right to left
        AWAY, // Up the grid
        TOWARDS, // Down the grid

        // 3D puzzles
        DOWN, // Down through grids
        UP, // Up through grids

        // 3D combination lock-style puzzles
        DIAMETRIC, // Through the disc
        CIRCULAR, // Around a disc

        // All of the above
        SNAKING, // Each letter could be anywhere, turn corners etc
        UNKNOWN, // If the puzzle does not define a direction or it is something different
        NONE // If the clues in this type of puzzle really don't have any direction
    };

    CrosswordClue(const QString& id, const QString& guess, const QString& solution, const QString& clue, Direction direction, const std::vector<VectorMath::Vec3i>& letterPositions);

    // TODO
    // ClueDirection getDirection() const;
    // QString getIdentifier() const; // Unique identifier for the clue
    // QString getClue() const; // The actual clue phrase

private:
    QString m_Id;
    QString m_Guess;
    QString m_Solution;
    QString m_Clue;
    Direction m_Direction;
    std::vector<VectorMath::Vec3i> m_LetterPositions;
};

}

#endif // CROSSWORDCLUE_H
