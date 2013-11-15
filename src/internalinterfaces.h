#ifndef INTERNALINTERFACES_H
#define INTERNALINTERFACES_H

#include "crosswordstate.h"
#include "formatscommon.h"

namespace InternalInterface
{
    // Gives grid scenes controlled access to the crossword state
    class CrosswordStateToGridScene
    {
    public:
        // Since everything can be edited on the grid, return a reference to the lot
        virtual Crossword::CrosswordState::ClueState& getClues() = 0;
        virtual Crossword::CrosswordState::GridState& getGrid() = 0;

        // Finer interface for adding clues
        virtual void addClue(const Crossword::CrosswordClue&) = 0;
        virtual const Crossword::CrosswordClue& getLastAddedClue() const = 0;

        virtual VectorMath::Vec3i getGridDimensions() const = 0;
        virtual VectorMath::Vec3i getNextCoordinateForDirection(Crossword::Formats::Direction, VectorMath::Vec3i index) const = 0;

        virtual Crossword::CrosswordState::FileFormat& getFileFormat() = 0;
    };

    class CrosswordStateToLoader
    {
    public:
        virtual Crossword::CrosswordState& getState() = 0;
    };

    class CrosswordStateToSaver
    {
    public:
        virtual const Crossword::CrosswordState& getState() const = 0;
    };

    class GridSceneToMainWindow
    {
    public:
        virtual bool canRedo() = 0;
        virtual bool canUndo() = 0;

        virtual void undo() = 0;
        virtual void redo() = 0;
    };
}

#endif // INTERNALINTERFACES_H
