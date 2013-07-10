#ifndef CROSSWORDBASE_H
#define CROSSWORDBASE_H

#include "crosswordstate.h"

#include <memory>

namespace Crossword
{

// An interface for accessing a crossword puzzle state.
class CrosswordBase
{
public:
    CrosswordBase();

    // If the crossword has a valid state
    // then it may be loaded or saved to disk
    bool isValid() const;

    // Replaces the current crossword state with a new default one
    void defaultState();

    CrosswordState& getState();
    const CrosswordState& getState() const;

protected:

private:
    std::unique_ptr<CrosswordState> m_State;
};

}

#endif // CROSSWORDBASE_H
