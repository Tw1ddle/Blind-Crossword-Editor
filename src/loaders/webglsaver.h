#ifndef WEBGLSAVER_H
#define WEBGLSAVER_H

#include "crosswordformat.h"
#include "crosswordsaver.h"

namespace Crossword
{

namespace Formats
{

class WebGLSaver : public CrosswordSaver
{
public:
    WebGLSaver();

    // Saves an XML file which is bundled with the WebGL code
    virtual QStringList save(const CrosswordState& state) const;
};

}
}

#endif // WEBGLSAVER_H
