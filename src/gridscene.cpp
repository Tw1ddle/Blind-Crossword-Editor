#include "gridscene.h"

#include <QString>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>

#include "gridclue.h"
#include "gridshape.h"

#include "newcrosswordcluepage.h"

namespace Grid
{

GridScene::GridScene(QObject* parent, InternalInterface::CrosswordStateToGridScene* const crosswordState) :
    QGraphicsScene(parent), m_CrosswordState(crosswordState), m_LeftMouseDown(false)
{    
    m_State = UserState::FILLING_GRID;
}

GridScene::~GridScene()
{
}

InternalInterface::CrosswordStateToGridScene* GridScene::getCrosswordState()
{
    return m_CrosswordState;
}

void GridScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsScene::mousePressEvent(event);

    // If mouse is down then
    if(event->button() == Qt::LeftButton)
    {
        m_LeftMouseDown = true;
    }

    // Open grid item setting box on right click
    if(event->button() == Qt::RightButton)
    {
    }
}

void GridScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_LeftMouseDown = false;
    }

    QGraphicsScene::mouseReleaseEvent(event);
}

void GridScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsScene::mouseMoveEvent(event);

    if(m_State == UserState::SELECTING_CLUE && m_LeftMouseDown)
    {
        QGraphicsItem* item;
        item = itemAt(event->scenePos(), QTransform());

        if(item)
        {
            item->setSelected(true);
        }
    }
}

void GridScene::keyPressEvent(QKeyEvent* event)
{
    QGraphicsScene::keyPressEvent(event);

    if(event->key() == Qt::Key_Control)
    {
        m_State = UserState::SELECTING_CLUE;
    }

    // Type letters into the grid
    if(m_State == UserState::FILLING_GRID)
    {
        QString keyText = event->text();

        auto shapes = getSelectedGridShapes();
        typeInItems(keyText, shapes);
    }

    // Delete text from grid squares
    if(event->key() == Qt::Key_Delete || event->key() == Qt::Key_Backspace)
    {
        auto shapes = getSelectedGridShapes();
        for(auto& shape : shapes)
        {
            shape->getItem().setText("");
            shape->update();
        }
    }
}

void GridScene::keyReleaseEvent(QKeyEvent* event)
{
    QGraphicsScene::keyReleaseEvent(event);

    if(event->key() == Qt::Key_Control)
    {
        if(m_State == UserState::SELECTING_CLUE)
        {
            // TODO wait for an action or choose an appropriate action here

            // addClue();
            // If the user adds the clue then clear the current selection
            // clearSelection();
            // m_State = UserState::FILLING_GRID;
        }
    }
}

QList<Grid::GridShape*> GridScene::getSelectedGridShapes()
{
    auto items = selectedItems();

    QList<Grid::GridShape*> shapes;

    for(auto& item : items)
    {
        auto shape = dynamic_cast<Grid::GridShape*>(item);

        if(shape)
        {
            shapes.push_back(shape);
        }
    }

    return shapes;
}

void GridScene::typeInItems(const QString& text, QList<GridShape*>& items)
{
    if((!text.isEmpty()) && items.size() == 1)
    {
        auto item = items.at(0);

        auto shapes = dynamic_cast<GridShape*>(item);

        if(shapes)
        {
            shapes->getItem().setText(text);
            shapes->update();
        }
    }
}

void GridScene::addClue()
{
    const QList<Grid::GridShape*> shapes = getSelectedGridShapes();

    // If there are shapes selected then construct a clue out of them
    if(!shapes.empty())
    {
        Editor::NewCrosswordCluePage newCluePage(getCrosswordState()->getClues(), shapes);

        int result = newCluePage.exec();
        if(result == QDialog::Accepted)
        {
            getCrosswordState()->addClue(newCluePage.getClue());
            const Crossword::CrosswordClue& clue = getCrosswordState()->getLastAddedClue();

            auto gridClue = new Grid::GridClue(clue, 50, 50); // TODO get width and height settings
            gridClue->setParentItem(shapes.at(0));
        }
    }
}

}
