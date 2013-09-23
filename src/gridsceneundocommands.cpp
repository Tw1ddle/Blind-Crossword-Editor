#include "gridsceneundocommands.h"

#include "gridshape.h"

Grid::EditShapeTextCommand::EditShapeTextCommand(GridShape* shape, const QString& newText) : m_Shape(shape),
    m_NewText(newText), m_OldText(shape->getItem().getText())
{
    shape->getItem().setText(newText);
    m_Shape->update();

    setText(QString("Edit %1 from \"%2\" to \"%3\"").arg(VectorMath::toString(shape->getItem().getCoordinate()), m_OldText, m_NewText));
}

Grid::EditShapeTextCommand::~EditShapeTextCommand()
{
}

void Grid::EditShapeTextCommand::undo()
{
    m_Shape->getItem().setText(m_OldText);
    m_Shape->update();
}

void Grid::EditShapeTextCommand::redo()
{
    m_Shape->getItem().setText(m_NewText);
    m_Shape->update();
}


Grid::SelectItemCommand::SelectItemCommand(QGraphicsItem* item) : m_Item(item)
{
    m_Item->setSelected(true);

    setText(QString("Select item"));
}

Grid::SelectItemCommand::~SelectItemCommand()
{
}

void Grid::SelectItemCommand::undo()
{
    m_Item->setSelected(false);
}

void Grid::SelectItemCommand::redo()
{
    m_Item->setSelected(true);
}

Grid::DeselectItemCommand::DeselectItemCommand(QGraphicsItem* item) : m_Item(item)
{
    m_Item->setSelected(false);

    setText(QString("Deselect item"));
}

Grid::DeselectItemCommand::~DeselectItemCommand()
{
}

void Grid::DeselectItemCommand::undo()
{
    m_Item->setSelected(true);
}

void Grid::DeselectItemCommand::redo()
{
    m_Item->setSelected(false);
}


Grid::ToggleItemVisibleCommand::ToggleItemVisibleCommand(QGraphicsItem* item) : m_Item(item), m_OldVisibility(item->isVisible())
{
    m_Item->setVisible(!m_OldVisibility);

    setText(QString("Toggle item visiblity"));
}

Grid::ToggleItemVisibleCommand::~ToggleItemVisibleCommand()
{
}

void Grid::ToggleItemVisibleCommand::undo()
{
    m_Item->setVisible(m_OldVisibility);
}

void Grid::ToggleItemVisibleCommand::redo()
{
    m_Item->setVisible(m_OldVisibility);
}


// This stops selecting the currently selected items - this does not clear the content of any items
Grid::ClearSelectionCommand::ClearSelectionCommand(QList<QGraphicsItem*> items) : m_OldSelection(items)
{
    for(auto& item : m_OldSelection)
    {
        item->setSelected(false);
    }

    setText(QString("Clear current selection"));
}

Grid::ClearSelectionCommand::~ClearSelectionCommand()
{
}

void Grid::ClearSelectionCommand::undo()
{
    for(auto& item : m_OldSelection)
    {
        item->setSelected(true);
    }
}

void Grid::ClearSelectionCommand::redo()
{
    for(auto& item : m_OldSelection)
    {
        item->setSelected(false);
    }
}

// Clears the contents of a shape
Grid::ClearShapeCommand::ClearShapeCommand(Grid::GridShape* shape) : m_Shape(shape), m_OldItem(shape->getItem())
{
    m_Shape->getItem().clear();
    m_Shape->update();

    setText(QString("Clear contents of shape at %1").arg(VectorMath::toString(m_Shape->getItem().getCoordinate())));
}

Grid::ClearShapeCommand::~ClearShapeCommand()
{
}

void Grid::ClearShapeCommand::undo()
{
    m_Shape->setItem(m_OldItem);
    m_Shape->update();
}

void Grid::ClearShapeCommand::redo()
{
    m_Shape->getItem().clear();
    m_Shape->update();
}
