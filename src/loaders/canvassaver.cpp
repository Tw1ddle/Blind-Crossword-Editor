#include "canvassaver.h"

#include "xmlsaver.h"
#include "utilities.h"

#include <QResource>

namespace Crossword
{

namespace Formats
{

CanvasSaver::CanvasSaver()
{
}

QStringList CanvasSaver::save(const CrosswordState& state) const
{
    // TODO check that this resource path works
    QResource resource(":/canvas/canvas.html");
    Q_ASSERT(resource.isValid());

    QStringList webTemplate = Utilities::readFile(resource.absoluteFilePath(), Utilities::INCLUDE_EMPTY_LINES);
    Q_ASSERT(!webTemplate.empty());

    XMLSaver xmlSaver;
    QStringList xml = xmlSaver.save(state);

    // The tag in the Canvas template where the xml state data will be inserted
    QRegExp replacementTag("<XML_CROSSWORD></XML_CROSSWORD>");

    int index = webTemplate.indexOf(replacementTag);

    if(index == -1)
    {
        return QStringList();
    }

    // TODO insert the xml into the webTemplate at the index
    xml += "TODO";

    return webTemplate;
}

}

}
