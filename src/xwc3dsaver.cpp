#include "xwc3dsaver.h"

using namespace Crossword;
using namespace Crossword::Formats;

XWC3DSaver::XWC3DSaver()
{
}

bool XWC3DSaver::save(const QString& filepath, const CrosswordState& state) const
{
    Q_UNUSED(filepath);
    Q_UNUSED(state);

    return false;
}
