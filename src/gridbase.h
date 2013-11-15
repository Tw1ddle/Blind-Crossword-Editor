#ifndef GRIDBASE_H
#define GRIDBASE_H

#include "internalinterfaces.h"

namespace Grid
{

class GridView;
class GridScene;

class GridBase : public InternalInterface::GridSceneToMainWindow
{
public:
    GridBase();
    ~GridBase();

    void setScene(Grid::GridView* view, InternalInterface::CrosswordStateToGridScene* const state);

    virtual void undo();
    virtual void redo();

    virtual bool canUndo();
    virtual bool canRedo();

private:
    std::unique_ptr<GridScene> m_Scene;
};

}

#endif // GRIDBASE_H
