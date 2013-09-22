#ifndef GRIDSCENEUNDOCOMMANDS_H
#define GRIDSCENEUNDOCOMMANDS_H

#include <QString>
#include <QUndoCommand>

#include "gridshape.h"
#include "griditem.h"

namespace Grid
{

class SelectGridItemCommand : public QUndoCommand
{
public:
    SelectGridItemCommand(QGraphicsItem* item);
    virtual ~SelectGridItemCommand();

    virtual void undo() override;
    virtual void redo() override;

private:
    QGraphicsItem* const m_Item;
};

class DeselectGridItemCommand : public QUndoCommand
{
public:
    DeselectGridItemCommand(QGraphicsItem* item);
    virtual ~DeselectGridItemCommand();

    virtual void undo() override;
    virtual void redo() override;

private:
    QGraphicsItem* const m_Item;
};

class EditGridShapeTextCommand : public QUndoCommand
{
public:
    EditGridShapeTextCommand(GridShape* shape, const QString& newText);
    virtual ~EditGridShapeTextCommand();

    virtual void undo() override;
    virtual void redo() override;

private:
    GridShape* const m_Shape;
    const QString m_OldText;
    const QString m_NewText;
};

}

#endif // GRIDSCENEUNDOCOMMANDS_H
