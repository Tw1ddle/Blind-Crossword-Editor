#include "crosswordexportsupportlocator.h"

#include "webglsaver.h"

namespace Crossword
{

namespace Formats
{

CrosswordExportSupportLocator::CrosswordExportSupportLocator()
{
    // Just register the formats on construction for now
    // Future support could include plugins that would require a more elaborate setup
    registerFormats();
}


void CrosswordExportSupportLocator::registerFormats()
{
    registerSaver(new CrosswordFormat(Formats::WEBGL100), new WebGLSaver());
}

}
}
