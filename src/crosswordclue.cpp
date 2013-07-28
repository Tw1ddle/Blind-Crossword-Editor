#include "crosswordclue.h"

using namespace Crossword;

CrosswordClue::CrosswordClue(const QString& guess, const QString& solution, const QString& number, const QString& clue, Direction direction, const std::vector<VectorMath::Vec3i>& letterPositions)
    : m_Guess(guess), m_Solution(solution), m_Number(number), m_Clue(clue), m_Direction(direction), m_LetterPositions(letterPositions)
{

}
