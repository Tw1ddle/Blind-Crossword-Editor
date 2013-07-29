#ifndef CROSSWORDBASE_H
#define CROSSWORDBASE_H

#include "crosswordstate.h"

#include <memory>

class QGraphicsView;

namespace Crossword
{

// Exposes parts of a crossword puzzle state to the main application.
class CrosswordBase
{
public:
    CrosswordBase();

    // If the crossword has a valid state
    // then it may be loaded or saved to disk
    bool isValid() const;

    // Only use non-const accessor for loading/saving states
    // TODO make loaders/savers friends of CrosswordBase instances or find a workaround
    CrosswordState& getState();
    const CrosswordState& getState() const;

protected:

public slots:
    // Replaces the current crossword state with a new default one
    void resetState();

    // Set a scene appropriate to the crossword state i.e. file format loaded
    virtual void setScene(QGraphicsView* view);
    // virtual void setMetadataEditor(); // TODO Set an appropriate metadata editor for the crossword state i.e. file format loaded

private:
    std::unique_ptr<CrosswordState> m_State;
};

}

#endif // CROSSWORDBASE_H
