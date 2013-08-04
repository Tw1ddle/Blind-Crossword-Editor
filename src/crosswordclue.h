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
    CrosswordClue(const QString& number, const QString& guess, const QString& solution, const QString& clue, const QString& direction, const std::vector<VectorMath::Vec3i>& letterPositions);

    // TODO
    // QString getDirection() const;
    // QString getIdentifier() const; // Unique identifier for the clue
    // QString getClue() const; // The actual clue phrase

private:
    QString m_Number;
    QString m_Guess;
    QString m_Solution;
    QString m_Clue;
    QString m_Direction;
    std::vector<VectorMath::Vec3i> m_LetterPositions;
};

}

#endif // CROSSWORDCLUE_H
