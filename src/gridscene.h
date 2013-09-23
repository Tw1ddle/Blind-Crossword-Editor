#ifndef GRIDSCENE_H
#define GRIDSCENE_H

#include <QGraphicsScene>
#include <QUndoStack>
#include <QUndoView>

#include "internalinterfaces.h"

namespace Grid
{

class GridShape;
class GridClue;

// Base class for scenes that display the crossword grids
class GridScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GridScene(QObject* parent, InternalInterface::CrosswordStateToGridScene* const crosswordState);
    virtual ~GridScene();

public slots:
    virtual void undo();
    virtual void redo();

protected:
    InternalInterface::CrosswordStateToGridScene* getCrosswordInterface();

    // Input handling
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void keyPressEvent(QKeyEvent* event) override;
    virtual void keyReleaseEvent(QKeyEvent* event) override;

    // Grid getters
    virtual GridShape* getGridShapeForCoordinate(VectorMath::Vec3i coordinate) = 0;
    QList<Grid::GridShape*> getSelectedGridShapes() const;
    const std::vector<GridShape*>& getGridShapes() const;
    void addGridShape(GridShape* shape);

    // Grid editing
    virtual void typeInItems(const QString& text, QList<GridShape*>& items);
    virtual void onSelectionChanged();

    // Modifying grid visibility
    void toggleClueVisibility();
    void toggleGridShapeVisibility();

    // Actions the user performs
    enum UserState
    {
        FILLING_GRID,
        SELECTING_CLUE
    };
    UserState m_State;

    // Add a command to the undo stack
    void addCommand(QUndoCommand* const command);
    void beginCommandMacro(const QString& description);
    void endCommandMacro();

private:
    void addClue();
    void createClueFromSelection();
    virtual bool selectNextGridShape() = 0; // Get the next item in the grid. Assumes puzzles have some concept of order or direction.
    virtual bool isNavigationKey(int keyCode) const = 0; // Controls allow user to most around the grid using certain keys

    std::vector<GridShape*> m_GridShapes;
    std::vector<GridClue*> m_GridClues;

    InternalInterface::CrosswordStateToGridScene* m_CrosswordState;
    bool m_LeftMouseDown;

    std::unique_ptr<QUndoStack> m_UndoStack;
    #ifdef QT_DEBUG
    std::unique_ptr<QUndoView> m_UndoView;
    #endif
};

}

#endif // GRIDSCENE_H
