#include "gridbase.h"

#include "gridview.h"
#include "gridscene2d.h"
#include "gridscene3d.h"
#include "gridscenerectangularlayers.h"
#include "gridscenecombinationlock.h"
#include "crosswordformat.h"

namespace Grid
{

GridBase::GridBase() : m_Scene(nullptr)
{
}

GridBase::~GridBase()
{
}

// Set a scene appropriate to the crossword state i.e. file format loaded
void GridBase::setScene(Grid::GridView* view, InternalInterface::CrosswordStateToGridScene* const state)
{
    // Create the appropriate scene type based on the puzzle format
    auto format = state->getFileFormat().m_Extension;
    auto formats2D = Crossword::Formats::get2DFormats();
    auto formats3D = Crossword::Formats::get3DFormats();

    if(formats2D.contains(format))
    {
        m_Scene = std::unique_ptr<GridScene2D>(new GridScene2D(view, state));
    }
    else if(formats3D.contains(format))
    {
        if(formats3D.find(format).value() == Crossword::Formats::FormatEnum::XWC3D)
        {
            m_Scene = std::unique_ptr<GridSceneRectangularLayers>(new GridSceneRectangularLayers(view, state));
        }
        else if(formats3D.find(format).value() == Crossword::Formats::FormatEnum::XWC3DR)
        {
            m_Scene = std::unique_ptr<GridSceneCombinationLock>(new GridSceneCombinationLock(view, state));
        }
    }
    else
    {
        // TODO If the format isn't one the program has a native loader for, then currently fail out
        Q_ASSERT(false);
    }

    QGraphicsScene* lastScene = view->scene();

    view->setScene(m_Scene.get());
    view->fitSceneInView();

    if(lastScene != nullptr)
    {
        delete lastScene;
    }
}

void GridBase::undo()
{
    m_Scene->undo();
}

void GridBase::redo()
{
    m_Scene->redo();
}

bool GridBase::canUndo()
{
    return m_Scene->canUndo();
}

bool GridBase::canRedo()
{
    return m_Scene->canRedo();
}

}
