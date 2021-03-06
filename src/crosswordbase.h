#ifndef CROSSWORDBASE_H
#define CROSSWORDBASE_H

#include "crosswordstate.h"

#include <memory>

#include "internalinterfaces.h"

namespace Grid
{
class GridView;
}

namespace Crossword
{

// Exposes parts of a crossword puzzle state to the main application.
class CrosswordBase : public InternalInterface::CrosswordStateToGridScene,
                      public InternalInterface::CrosswordStateToLoader,
                      public InternalInterface::CrosswordStateToSaver
{
public:
    CrosswordBase();
    virtual ~CrosswordBase();

    // If the crossword has a valid state
    // then it may be loaded or saved to disk
    bool isValid() const;

    // Whether the crossword is in a state that allows it to be saved to disk
    // Difference from isValid is that this might have a stronger precondition
    bool isSaveable() const;

    // Has the state been saved to disk before.
    // If a user creates a new crossword but does not save it, then it will not have a filename...
    bool hasFilepath() const;

    QString getFilepath() const;
    QString getFilename() const;

    // Only use non-const accessor for loading/saving states - see interfacess
    CrosswordState& getState() override;
    const CrosswordState& getState() const override;

    // What grid scenes should see of the crossword state
    virtual CrosswordState::ClueState& getClues() override;
    virtual CrosswordState::GridState& getGrid() override;

    void addClue(const CrosswordClue& clue) override;
    virtual const Crossword::CrosswordClue& getLastAddedClue() const override;

    virtual Crossword::CrosswordState::FileFormat& getFileFormat() override;

    // Given an item in the grid, find the index of the next one along in any given direction
    // If the index would run off the edge of a grid, it loops back around to the opposite side
    virtual VectorMath::Vec3i getNextCoordinateForDirection(Crossword::Formats::Direction, VectorMath::Vec3i coordinate) const override;
    virtual VectorMath::Vec3i getGridDimensions() const override;

protected:

public slots:
    // Replaces the current crossword state with a new default one
    void resetState();

    // Replaces the current state with the provided state
    void setState(std::unique_ptr<CrosswordState>& nextState);

    // virtual void setMetadataEditor(); // TODO Set an appropriate metadata editor for the crossword state
    // i.e. the file format loaded... and for other dialogs too...

private:
    std::unique_ptr<CrosswordState> m_State;
};

}

#endif // CROSSWORDBASE_H
