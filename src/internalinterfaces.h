#ifndef INTERNALINTERFACES_H
#define INTERNALINTERFACES_H

#include "crosswordstate.h"

namespace InternalInterface
{
    // Gives grid scenes controlled access to the crossword state
    class CrosswordStateToGridScene
    {
    public:
        // Since everything can be edited on the grid, return a reference to the lot
        virtual Crossword::CrosswordState::ClueState& getClues() = 0;
        virtual Crossword::CrosswordState::GridState& getGrid() = 0;
    };
}

#endif // INTERNALINTERFACES_H
