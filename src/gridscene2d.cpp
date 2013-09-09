#include "gridscene2d.h"

#include <QKeyEvent>

namespace Grid
{

GridScene2D::GridScene2D(QObject* parent, InternalInterface::CrosswordStateToGridScene* const crosswordState) : GridScene(parent, crosswordState)
{
    m_TypingDirection = RIGHT;
    addGrid();
}

void GridScene2D::keyPressEvent(QKeyEvent* event)
{
    GridScene::keyPressEvent(event);

    auto lastTypingDirection = m_TypingDirection;

    // Set the direction of typing
    auto key = event->key();
    if(key == Qt::Key_Right || key == Qt::Key_Left || key == Qt::Key_Up || key == Qt::Key_Down)
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

        if(lastTypingDirection == m_TypingDirection)
        {
            advance();
        }
    }

    // TODO Type in the letter and select the next available puzzle square
}

void GridScene2D::keyReleaseEvent(QKeyEvent* event)
{
    GridScene::keyReleaseEvent(event);
}

void GridScene2D::addGrid()
{
    Crossword::CrosswordState::GridState& gridModel = getCrosswordState()->getGrid();

    QGraphicsItemGroup* gridItem = new QGraphicsItemGroup();

    for(unsigned int i = 0; i < gridModel.m_Grid.size(); i++)
    {
        auto coordinate = std::get<Crossword::CrosswordState::GridState::COORDINATE>(gridModel.m_Grid.at(i));
        Crossword::CrosswordItem& letter = std::get<Crossword::CrosswordState::GridState::SOLUTION>(gridModel.m_Grid.at(i));

        // TODO get size setting
        Grid::GridSquare* square = new Grid::GridSquare(letter, 100, 100);

        // TODO get item spacing setting
        square->setPos(coordinate.x() * 100, coordinate.y() * 100);

        square->setParentItem(gridItem);
        addItem(square);
    }

    addItem(gridItem);
}

bool GridScene2D::advance()
{
    // TODO

    switch(m_TypingDirection)
    {
    case RIGHT:
        break;
    case LEFT:
        break;
    case UP:
        break;
    case DOWN:
        break;
    }

    return false;
}

}
