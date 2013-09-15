#include "webglsaver.h"

#include "xmlsaver.h"

#include <QFileInfo>
#include <QDir>

namespace Crossword
{

namespace Formats
{

WebGLSaver::WebGLSaver()
{
}

bool WebGLSaver::save(const QString& filepath, const CrosswordState& state) const
{
    XMLSaver xmlSaver;

    xmlSaver.save(filepath, state);

    // Read a web template and insert the required data (JSON or XML) into the file
    // TODO ":/webtemplates/webgl.html"

    return false;
}

}
}
