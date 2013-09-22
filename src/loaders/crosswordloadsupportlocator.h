#ifndef CROSSWORDLOADSUPPORTLOCATOR_H
#define CROSSWORDLOADSUPPORTLOCATOR_H

#include "crosswordformatsupportlocator.h"

namespace Crossword
{

namespace Formats
{

// Regular loading and saving to disk support
class CrosswordLoadSupportLocator : public CrosswordFormatSupportLocator
{
public:
    CrosswordLoadSupportLocator();

private:
    virtual void registerFormats() override;
};

}
}

#endif // CROSSWORDLOADSUPPORTLOCATOR_H
