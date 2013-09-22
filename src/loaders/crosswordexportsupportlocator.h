#ifndef CROSSWORDEXPORTSUPPORTLOCATOR_H
#define CROSSWORDEXPORTSUPPORTLOCATOR_H

#include "crosswordformatsupportlocator.h"

namespace Crossword
{

namespace Formats
{

// Export to web, copying to clipboard etc support
class CrosswordExportSupportLocator : public CrosswordFormatSupportLocator
{
public:
    CrosswordExportSupportLocator();

private:
    virtual void registerFormats() override;
};

}
}

#endif // CROSSWORDEXPORTSUPPORTLOCATOR_H
