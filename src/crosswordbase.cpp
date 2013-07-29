#include "crosswordbase.h"

#include <QGraphicsView>

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

void CrosswordBase::resetState()
{
    m_State.swap(std::unique_ptr<CrosswordState>(new CrosswordState));
}

void CrosswordBase::setScene(QGraphicsView* view)
{
    Q_UNUSED(view);
    // TODO Find an appropriate scene to set
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
