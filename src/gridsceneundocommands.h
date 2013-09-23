#ifndef GRIDSCENEUNDOCOMMANDS_H
#define GRIDSCENEUNDOCOMMANDS_H

#include <QString>
#include <QUndoCommand>

#include "gridshape.h"
#include "griditem.h"

namespace Grid
{

class SelectItemCommand : public QUndoCommand
{
public:
    SelectItemCommand(QGraphicsItem* item);
    virtual ~SelectItemCommand();

    virtual void undo() override;
    virtual void redo() override;

private:
    QGraphicsItem* const m_Item;
};

class DeselectItemCommand : public QUndoCommand
{
public:
    DeselectItemCommand(QGraphicsItem* item);
    virtual ~DeselectItemCommand();

    virtual void undo() override;
    virtual void redo() override;

private:
    QGraphicsItem* const m_Item;
};

class EditShapeTextCommand : public QUndoCommand
{
public:
    EditShapeTextCommand(GridShape* shape, const QString& newText);
    virtual ~EditShapeTextCommand();

    virtual void undo() override;
    virtual void redo() override;

private:
    GridShape* const m_Shape;
    const QString m_OldText;
    const QString m_NewText;
};

class ClearShapeCommand : public QUndoCommand
{
public:
    ClearShapeCommand(GridShape* shape);
    virtual ~ClearShapeCommand();

    virtual void undo() override;
    virtual void redo() override;

private:
    GridShape* const m_Shape;
    const Crossword::CrosswordItem m_OldItem;
};

class ToggleItemVisibleCommand : public QUndoCommand
{
public:
    ToggleItemVisibleCommand(QGraphicsItem* item);
    virtual ~ToggleItemVisibleCommand();

    virtual void undo() override;
    virtual void redo() override;

private:
    QGraphicsItem* const m_Item;
    const bool m_OldVisibility;
};

class ClearSelectionCommand : public QUndoCommand
{
public:
    ClearSelectionCommand(QList<QGraphicsItem*> items);
    virtual ~ClearSelectionCommand();

    virtual void undo() override;
    virtual void redo() override;

private:
    const QList<QGraphicsItem*> m_OldSelection;
};

}

#endif // GRIDSCENEUNDOCOMMANDS_H
