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

InternalInterface::CrosswordStateToGridScene* GridScene::getCrosswordInterface()
{
    return m_CrosswordState;
}

void GridScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsScene::mousePressEvent(event);

    if(Qt::LeftButton == event->button())
    {
        m_LeftMouseDown = true;
    }

    // Open grid item setting box on right click
    if(Qt::RightButton == event->button())
    {
        // TODO
    }
}

void GridScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if(Qt::LeftButton == event->button())
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

    auto key = event->key();

    if(Qt::Key_Control == key)
    {
        m_State = UserState::SELECTING_CLUE;
    }

    // Clear grid square(s)
    if(Qt::Key_Delete == key || Qt::Key_Backspace == key)
    {
        auto shapes = getSelectedGridShapes();
        for(auto& shape : shapes)
        {
            shape->clear();
            shape->update();
        }
    }

    if(UserState::FILLING_GRID == m_State && !isNavigationKey(key))
    {
        // Insert the input into the grid
        QString keyText = event->text();

        auto shapes = getSelectedGridShapes();
        typeInItems(keyText, shapes);

        selectNextGridShape();
    }

    event->accept();
}

void GridScene::keyReleaseEvent(QKeyEvent* event)
{
    QGraphicsScene::keyReleaseEvent(event);

    if(Qt::Key_Control == event->key())
    {
        if(UserState::SELECTING_CLUE == m_State)
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

std::vector<GridShape*>& GridScene::getGridShapes()
{
    return m_GridShapes;
}

void GridScene::typeInItems(const QString& text, QList<GridShape*>& items)
{
    if((!text.isEmpty()) && items.size() == 1)
    {
        auto item = items.at(0);

        auto shape = dynamic_cast<GridShape*>(item);

        if(shape)
        {
            shape->getItem().setText(text);
            shape->update();
        }
    }
}

void GridScene::onSelectionChanged()
{

}

void GridScene::addClue()
{
    const QList<Grid::GridShape*> shapes = getSelectedGridShapes();

    // If there are shapes selected then construct a clue out of them
    if(!shapes.empty())
    {
        Editor::NewCrosswordCluePage newCluePage(getCrosswordInterface()->getClues(), shapes);

        int result = newCluePage.exec();
        if(QDialog::Accepted == result)
        {
            getCrosswordInterface()->addClue(newCluePage.getClue());
            const Crossword::CrosswordClue& clue = getCrosswordInterface()->getLastAddedClue();

            auto gridClue = new Grid::GridClue(clue, 50, 50); // TODO get width and height settings
            gridClue->setParentItem(shapes.at(0));
        }
    }
}

}
