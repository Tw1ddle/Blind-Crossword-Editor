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
    CrosswordClue(const QString& number, const QString& guess, const QString& solution, const QString& clue, const QString& direction, const QString& componentLengths, const std::vector<VectorMath::Vec3i>& letterPositions);

    const QString& getIdentifier() const;
    const QString& getNumber() const;
    const QString& getGuess() const;
    const QString& getSolution() const;
    const QString& getClue() const;
    const QString& getDirection() const;
    const QString& getComponentLengths() const;

    const std::vector<VectorMath::Vec3i>& getLetterPositions() const;

private:
    QString m_Identifier;
    QString m_Number;
    QString m_Guess;
    QString m_Solution;
    QString m_Clue;
    QString m_Direction;
    QString m_ComponentLengths;
    std::vector<VectorMath::Vec3i> m_LetterPositions;
};

}

#endif // CROSSWORDCLUE_H
