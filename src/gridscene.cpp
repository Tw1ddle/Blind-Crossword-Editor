#include "gridscene.h"

#include <QString>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>

#include "gridclue.h"
#include "gridshape.h"
#include "gridsceneundocommands.h"

#include "newcrosswordcluepage.h"

namespace Grid
{

GridScene::GridScene(QObject* parent, InternalInterface::CrosswordStateToGridScene* const crosswordState) :
    QGraphicsScene(parent), m_CrosswordState(crosswordState), m_LeftMouseDown(false)
{    
    m_UndoStack = std::unique_ptr<QUndoStack>(new QUndoStack());

    #ifdef QT_DEBUG
    m_UndoView = std::unique_ptr<QUndoView>(new QUndoView(m_UndoStack.get()));
    m_UndoView->setWindowTitle(tr("Undo Command List"));
    m_UndoView->show();
    #endif

    m_State = UserState::FILLING_GRID;
}

GridScene::~GridScene()
{
}

void GridScene::undo()
{
    m_UndoStack->undo();
}

void GridScene::redo()
{
    m_UndoStack->redo();
}

bool GridScene::canUndo()
{
    return m_UndoStack->canUndo();
}

bool GridScene::canRedo()
{
    return m_UndoStack->canRedo();
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
        Editor::NewCrosswordCluePage newCrosswordCluePage(m_CrosswordState->getClues(), getSelectedGridShapes());

        newCrosswordCluePage.exec();
    }
}

// TODO reimplement the base class events so it's possible to put undo/redos in easier
void GridScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsScene::mouseReleaseEvent(event);

    if(Qt::LeftButton == event->button())
    {
        m_LeftMouseDown = false;
    }
}

void GridScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsScene::mouseMoveEvent(event);

    if(m_State == UserState::SELECTING_CLUE && m_LeftMouseDown)
    {
        QGraphicsItem* item = itemAt(event->scenePos(), QTransform());

        // TODO what about selections that overlap themselves? e.g. overlapping snaking clues
        if(item && !item->isSelected())
        {
            // TODO merge sequences of these selection commands
            addCommand(new SelectItemCommand(item));
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

        beginCommandMacro(QString("Clear %1 shapes").arg(QString::number(shapes.size())));
        for(auto& shape : shapes)
        {
            addCommand(new ClearShapeCommand(shape));
        }
        endCommandMacro();
    }

    if(UserState::FILLING_GRID == m_State && !isNavigationKey(key))
    {
        QString keyText = event->text();

        auto shapes = getSelectedGridShapes();
        typeInItems(keyText, shapes);

        selectNextGridShape();
    }

    // Enter a clue
    if(Qt::Key_Return == key && UserState::SELECTING_CLUE == m_State)
    {
        addClue();

        clearSelection();

        m_State = UserState::FILLING_GRID;
    }

    event->accept();
}

void GridScene::keyReleaseEvent(QKeyEvent* event)
{
    QGraphicsScene::keyReleaseEvent(event);
}

std::vector<Grid::GridShape*> GridScene::getSelectedGridShapes() const
{
    return m_GridShapeSelection;
}

const std::vector<GridShape*>& GridScene::getGridShapes() const
{
    return m_GridShapes;
}

void GridScene::addGridShape(GridShape* shape)
{
    m_GridShapes.push_back(shape);
}

void GridScene::addClue()
{
    const std::vector<Grid::GridShape*> shapes = getSelectedGridShapes();

    // If there are shapes selected then construct a clue out of them
    if(!shapes.empty())
    {
        Editor::NewCrosswordCluePage newCluePage(getCrosswordInterface()->getClues(), shapes);

        if(QDialog::Accepted == newCluePage.exec())
        {
            getCrosswordInterface()->addClue(newCluePage.getClue());
            const Crossword::CrosswordClue& clue = getCrosswordInterface()->getLastAddedClue();

            auto gridClue = new Grid::GridClue(clue, 50, 50); // TODO get width and height settings
            gridClue->setParentItem(shapes.at(0));

            // TODO add clue to the clues list
        }
    }
}

void GridScene::typeInItems(const QString& text, std::vector<GridShape*>& items)
{
    if((!text.isEmpty()) && items.size() == 1)
    {
        auto item = items.at(0);

        auto shape = dynamic_cast<GridShape*>(item);

        if(shape)
        {
            addCommand(new EditShapeTextCommand(shape, text));
        }
    }
}

void GridScene::onSelectionChanged()
{
    QGraphicsItem* item = qobject_cast<QGraphicsItem*>(sender());

    GridShape* shape = dynamic_cast<GridShape*>(item);

    if(shape)
    {
        if(shape->isSelected())
        {
            m_GridShapeSelection.push_back(shape);
        }
        else
        {
            m_GridShapeSelection.push_back(shape);
        }
    }
}

void GridScene::toggleGridShapeVisibility()
{
    beginCommandMacro("Toggle grid shape visibility");
    for(GridShape* shape : m_GridShapes)
    {
        addCommand(new ToggleItemVisibleCommand(shape));
    }
    endCommandMacro();
}

void GridScene::toggleClueVisibility()
{
    beginCommandMacro("Toggle clue visibility");
    for(GridClue* clue : m_GridClues)
    {
        addCommand(new ToggleItemVisibleCommand(clue));
    }
    endCommandMacro();
}

void GridScene::addCommand(QUndoCommand* const command)
{
    m_UndoStack->push(command);
}

void GridScene::beginCommandMacro(const QString& description)
{
    m_UndoStack->beginMacro(description);
}

void GridScene::endCommandMacro()
{
    m_UndoStack->endMacro();
}

}
