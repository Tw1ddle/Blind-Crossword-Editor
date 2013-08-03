#include "crosswordbase.h"

#include <QGraphicsView>

#include "gridscene2d.h"
#include "gridscene3d.h"
#include "gridscenerectangularlayers.h"
#include "gridscenecombinationlock.h"

#include "crosswordformat.h"

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

CrosswordState::ClueState& CrosswordBase::getClues()
{
    return m_State->m_ClueState;
}

CrosswordState::GridState& CrosswordBase::getGrid()
{
    return m_State->m_GridState;
}

void CrosswordBase::resetState()
{
    auto blankState = std::unique_ptr<CrosswordState>(new CrosswordState);

    m_State.swap(blankState);
}

void CrosswordBase::setScene(QGraphicsView* view)
{
    // Create the appropriate scene type based on the puzzle format
    auto format = m_State->m_FileFormat.m_Extension;
    auto formats2D = Formats::get2DFormats();
    auto formats3D = Formats::get3DFormats();

    QGraphicsScene* scene = nullptr;

    if(formats2D.contains(format))
    {
        scene = new Grid::GridScene2D(view, this);
    }
    else if(formats3D.contains(format))
    {
        if(formats3D.find(format).value() == Formats::FormatEnum::XWC3D)
        {
            scene = new Grid::GridSceneRectangularLayers(view, this);
        }
        else if(formats3D.find(format).value() == Formats::FormatEnum::XWC3DR)
        {
            scene = new Grid::GridSceneCombinationLock(view, this);
        }
    }
    else
    {
        // If the format isn't one the program has a native loader for but we've got this far, assume it's a 2D puzzle
        Q_ASSERT(false); // TODO remove if proper support for plugin loaders/savers is added

        scene = new Grid::GridScene2D(view, this);
    }

    if(view->scene() != nullptr)
    {
        delete view->scene();
    }

    view->setScene(scene);
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
