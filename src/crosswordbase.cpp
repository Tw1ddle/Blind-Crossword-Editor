#include "crosswordbase.h"

namespace Crossword
{

CrosswordBase::CrosswordBase()
{
    m_State = std::unique_ptr<CrosswordState>(new CrosswordState);
}

bool CrosswordBase::isValid() const
{
    // A lot of sanity checking about the state of the puzzle should go here

    return true;
}

void CrosswordBase::defaultState()
{
    m_State.swap(std::unique_ptr<CrosswordState>(new CrosswordState));
}

CrosswordState& CrosswordBase::getState()
{
    return *(m_State.get());
}

const CrosswordState& CrosswordBase::getState() const
{
    return *(m_State.get());
}

}
