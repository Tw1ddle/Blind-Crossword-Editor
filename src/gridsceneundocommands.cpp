#include "gridsceneundocommands.h"

Grid::EditGridShapeTextCommand::EditGridShapeTextCommand(GridShape* shape, const QString& newText) : m_Shape(shape),
    m_NewText(newText), m_OldText(shape->getItem().getText())
{
    shape->getItem().setText(newText);
    m_Shape->update();

    setText(QString("Edit %1 from \"%2\" to \"%3\"").arg(VectorMath::toString(shape->getItem().getCoordinate()), m_OldText, m_NewText));
}

Grid::EditGridShapeTextCommand::~EditGridShapeTextCommand()
{
}

void Grid::EditGridShapeTextCommand::undo()
{
    m_Shape->getItem().setText(m_OldText);
    m_Shape->update();
}

void Grid::EditGridShapeTextCommand::redo()
{
    m_Shape->getItem().setText(m_NewText);
    m_Shape->update();
}


Grid::SelectGridItemCommand::SelectGridItemCommand(QGraphicsItem* item) : m_Item(item)
{
    m_Item->setSelected(true);

    setText(QString("Selected item"));
}

Grid::SelectGridItemCommand::~SelectGridItemCommand()
{
}

void Grid::SelectGridItemCommand::undo()
{
    m_Item->setSelected(false);
}

void Grid::SelectGridItemCommand::redo()
{
    m_Item->setSelected(true);
}

Grid::DeselectGridItemCommand::DeselectGridItemCommand(QGraphicsItem* item) : m_Item(item)
{
    m_Item->setSelected(false);

    setText(QString("Deselected item"));
}

Grid::DeselectGridItemCommand::~DeselectGridItemCommand()
{
}

void Grid::DeselectGridItemCommand::undo()
{
    m_Item->setSelected(true);
}

void Grid::DeselectGridItemCommand::redo()
{
    m_Item->setSelected(false);
}
