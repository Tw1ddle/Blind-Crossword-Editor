#include "crosswordclue.h"

using namespace Crossword;

CrosswordClue::CrosswordClue(const QString& number, const QString& guess, const QString& solution, const QString& clue, const QString& direction, const QString& componentLengths, const std::vector<VectorMath::Vec3i> letterPositions)
    : m_Number(number), m_Guess(guess), m_Solution(solution), m_Clue(clue), m_Direction(direction), m_ComponentLengths(componentLengths), m_LetterPositions(letterPositions)
{
    if(m_ComponentLengths.isEmpty())
    {
        m_ComponentLengths = QString::number(getLetterPositions().size());
    }

    // TODO make threadsafe solution
    static int identifier_index = 0;

    m_Identifier = QString::number(identifier_index);

    identifier_index++;

    Q_ASSERT(!letterPositions.empty());
    Q_ASSERT(!number.isEmpty());
    Q_ASSERT(!clue.isEmpty());
    Q_ASSERT(!direction.isEmpty());
}

const QString& CrosswordClue::getIdentifier() const
{
    return m_Identifier;
}

const QString& CrosswordClue::getNumber() const
{
    return m_Number;
}

const QString& CrosswordClue::getGuess() const
{
    return m_Guess;
}

const QString& CrosswordClue::getSolution() const
{
    return m_Solution;
}

const QString& CrosswordClue::getClue() const
{
    return m_Clue;
}

const QString& CrosswordClue::getDirection() const
{
    return m_Direction;
}

const QString& CrosswordClue::getComponentLengths() const
{
    return m_ComponentLengths;
}

const std::vector<VectorMath::Vec3i>& CrosswordClue::getLetterPositions() const
{
    return m_LetterPositions;
}
