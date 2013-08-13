#include "crosswordclue.h"

using namespace Crossword;

CrosswordClue::CrosswordClue(const QString& number, const QString& guess, const QString& solution, const QString& clue, const QString& direction, const std::vector<VectorMath::Vec3i>& letterPositions)
    : m_Number(number), m_Guess(guess), m_Solution(solution), m_Clue(clue), m_Direction(direction), m_LetterPositions(letterPositions)
{

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

const std::vector<VectorMath::Vec3i>& CrosswordClue::getLetterPositions() const
{
    return m_LetterPositions;
}
