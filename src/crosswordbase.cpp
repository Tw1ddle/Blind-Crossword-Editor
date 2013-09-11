#include "crosswordbase.h"

#include <QGraphicsView>
#include <QFileInfo>

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
    // TODO A lot of sanity checking about the state of the puzzle should go here

    return true;
}

bool CrosswordBase::isSaveable() const
{
    return isValid();
}

bool CrosswordBase::hasFilepath() const
{
    return !m_State->m_DataSources.m_PuzzleFilePath.isEmpty();
}

QString CrosswordBase::getFilepath() const
{
    Q_ASSERT(hasFilepath());

    return m_State->m_DataSources.m_PuzzleFilePath;
}

QString CrosswordBase::getFilename() const
{
    Q_ASSERT(hasFilepath());

    QFileInfo info(getFilepath());

    return info.fileName();
}

CrosswordState::ClueState& CrosswordBase::getClues()
{
    return m_State->m_ClueState;
}

CrosswordState::GridState& CrosswordBase::getGrid()
{
    return m_State->m_GridState;
}

void CrosswordBase::addClue(const CrosswordClue& clue)
{
    m_State->m_ClueState.m_Clues.push_back(clue);
}

const CrosswordClue& CrosswordBase::getLastAddedClue() const
{
    return m_State->m_ClueState.m_Clues.back();
}

VectorMath::Vec3i CrosswordBase::getNextCoordinateForDirection(Formats::Direction direction, VectorMath::Vec3i coordinate) const
{
    VectorMath::Vec3i next(0, 0, 0);

    switch(direction)
    {
    // Get the next item
    case Formats::Direction::ACROSS:
        next = coordinate + VectorMath::Vec3i(1, 0, 0);
        break;

    case Formats::Direction::BACKWARDS:
        next = coordinate + VectorMath::Vec3i(-1, 0, 0);
        break;

    case Formats::Direction::AWAY:
        next = coordinate + VectorMath::Vec3i(0, 1, 0);
        break;

    case Formats::Direction::TOWARDS:
        next = coordinate + VectorMath::Vec3i(0, -1, 0);
        break;

    case Formats::Direction::DOWN:
        next = coordinate + VectorMath::Vec3i(0, 0, 1);
        break;

    case Formats::Direction::UP:
        next = coordinate + VectorMath::Vec3i(0, 0, -1);
        break;


    case Formats::Direction::DIAMETRIC:
        // TODO
        // ...
        break;
    case Formats::Direction::CLOCKWISE:
        next = coordinate + VectorMath::Vec3i(0, 1, 0);
        break;

    case Formats::Direction::ANTICLOCKWISE:
        next = coordinate + VectorMath::Vec3i(0, -1, 0);
        break;


    // These are invalid directions to ask for a 'next' item
    case Formats::Direction::SNAKING:
        Q_ASSERT(false);
        break;

    case Formats::Direction::UNKNOWN:
        Q_ASSERT(false);
        break;
    default:
        Q_ASSERT(false);
    }

    auto dimensions = m_State->m_GridState.m_Dimensions;

    // Move the coordinate into the grid space (in case it ran over the edges)
    next %= dimensions;
    if(next.x() < 0)
    {
        next.set(next.x() + dimensions.x(), next.y(), next.z());
    }
    if(next.y() < 0)
    {
        next.set(next.x(), next.y() + dimensions.y(), next.z());
    }
    if(next.z() < 0)
    {
        next.set(next.x(), next.y(), next.z() + dimensions.z());
    }

    return next;
}

VectorMath::Vec3i CrosswordBase::getGridDimensions() const
{
    auto dimensions = m_State->m_GridState.m_Dimensions;

    return dimensions;
}

void CrosswordBase::resetState()
{
    auto blankState = std::unique_ptr<CrosswordState>(new CrosswordState);

    m_State.swap(blankState);
}

void CrosswordBase::setState(std::unique_ptr<CrosswordState>& nextState)
{
    m_State.swap(nextState);
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
        // TODO
        // If the format isn't one the program has a native loader for but we've got this far, assume it's a 2D puzzle
        Q_ASSERT(false); // Remove this failure if proper support for plugin-based loaders/savers is added
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
