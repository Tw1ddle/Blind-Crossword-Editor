#include "webglsaver.h"

namespace Crossword
{

namespace Formats
{

WebGLSaver::WebGLSaver()
{
}

bool WebGLSaver::save(const QString& filepath, const CrosswordState& state) const
{
    Q_UNUSED(filepath);
    Q_UNUSED(state);

    // TODO read a web template and insert the required data (JSON or XML?) into the file
    // Copy all the necessary files to a directory with the same name as the filename...
    // Then open them in a web browser (probable use case)

    return false;
}

}
}
