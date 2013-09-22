#include "crosswordloadsupportlocator.h"

#include "xwcloader.h"
#include "xwcsaver.h"
#include "xwc3dloader.h"
#include "xwc3dsaver.h"
#include "acrosslitetextloader.h"
#include "acrosslitetextsaver.h"
#include "plaintextsaver.h"
#include "xmlsaver.h"

namespace Crossword
{

namespace Formats
{

CrosswordLoadSupportLocator::CrosswordLoadSupportLocator()
{
    registerFormats();
}


void CrosswordLoadSupportLocator::registerFormats()
{
    // Load and save XWC files (v1.0.1)
    registerLoader(new CrosswordFormat(XWC101), new XWCLoader());
    registerSaver(new CrosswordFormat(XWC101), new XWCSaver());

    // Load and save XWC3D files (v1.0.0)
    registerLoader(new CrosswordFormat(XWC3D100), new XWC3DLoader());
    registerSaver(new CrosswordFormat(XWC3D100), new XWC3DSaver());

    // Across Lite Text support
    //registerLoader(new CrosswordFormat(ACROSSLITETEXT), new AcrossLiteTextLoader());
    // registerSaver(new CrosswordFormat(ACROSSLITETEXT), new AcrossLiteTextSaver());

    // TODO More file support
}

}
}
