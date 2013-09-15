#include "gridscene2d.h"

#include <QKeyEvent>

namespace Grid
{

GridScene2D::GridScene2D(QObject* parent, InternalInterface::CrosswordStateToGridScene* const crosswordState) : GridScene(parent, crosswordState)
{
    m_TypingDirection = RIGHT;
    addGrid();
}

void GridScene2D::addGrid()
{
    Crossword::CrosswordState::GridState& gridModel = getCrosswordInterface()->getGrid();

    QGraphicsItemGroup* gridItem = new QGraphicsItemGroup();

    for(unsigned int i = 0; i < gridModel.m_Grid.size(); i++)
    {
        auto coordinate = std::get<Crossword::CrosswordState::GridState::ITEM>(gridModel.m_Grid.at(i)).getCoordinate();
        Crossword::CrosswordItem& letter = std::get<Crossword::CrosswordState::GridState::ITEM>(gridModel.m_Grid.at(i));

        // TODO get size setting
        Grid::GridSquare* square = new Grid::GridSquare(letter, 100, 100);

        // TODO get item spacing setting
        square->setPos(coordinate.x() * 100, coordinate.y() * 100);

        square->setParentItem(gridItem);
        addItem(square);

        getGridShapes().push_back(square);
    }

    addItem(gridItem);
}

void GridScene2D::keyPressEvent(QKeyEvent* event)
{
    // Set the direction of typing with the arrow keys (perspective of looking at a 2D grid top-down)
    auto key = event->key();

    if(isNavigationKey(key))
    {
        switch (key)
        {
        case Qt::Key_Right:
            m_TypingDirection = RIGHT;
            break;
        case Qt::Key_Left:
            m_TypingDirection = LEFT;
            break;
        case Qt::Key_Up:
            m_TypingDirection = UP;
            break;
        case Qt::Key_Down:
            m_TypingDirection = DOWN;
            break;
        }
        selectNextGridShape();
    }

    GridScene::keyPressEvent(event);

    event->accept();
}

void GridScene2D::keyReleaseEvent(QKeyEvent* event)
{
    GridScene::keyReleaseEvent(event);
}

bool GridScene2D::selectNextGridShape()
{
    auto shapes = getSelectedGridShapes();

    // If more than one shape is selected then moving pointer in a direction is ambiguous/impossible
    if(shapes.size() != 1)
    {
        return false;
    }

    auto current = shapes.at(0)->getItem().getCoordinate();
    VectorMath::Vec3i next(0, 0, 0);
    auto state = getCrosswordInterface();

    switch(m_TypingDirection)
    {
    case RIGHT:
        next = state->getNextCoordinateForDirection(Crossword::Formats::Direction::ACROSS, current);
        break;
    case LEFT:
        next = state->getNextCoordinateForDirection(Crossword::Formats::Direction::BACKWARDS, current);
        break;
    case UP:
        // Since (0,0) is at the upper left, pressing "towards" the front of the puzzle actually goes "down" the page
        next = state->getNextCoordinateForDirection(Crossword::Formats::Direction::TOWARDS, current);
        break;
    case DOWN:
        // Ditto above
        next = state->getNextCoordinateForDirection(Crossword::Formats::Direction::AWAY, current);
        break;
    }

    auto shape = getGridShapeForCoordinate(next);

    clearSelection();
    shape->setSelected(true);

    return true;
}

GridShape* GridScene2D::getGridShapeForCoordinate(VectorMath::Vec3i coordinate)
{
    return getGridShapes().at(coordinate.x() + coordinate.y() * getCrosswordInterface()->getGridDimensions().x());
}

bool GridScene2D::isNavigationKey(int keyCode) const
{
    bool isArrow = (keyCode == Qt::Key_Right ||
                  keyCode == Qt::Key_Left ||
                  keyCode == Qt::Key_Up ||
                  keyCode == Qt::Key_Down);

    return isArrow;
}

}
