#include "crosswordformat.h"

namespace Crossword
{
namespace Formats
{

CrosswordFormat::CrosswordFormat(const QString& fileExtension, const QString& version) : m_Extension(fileExtension), m_Version(version)
{
}

CrosswordFormat::CrosswordFormat(const std::pair<QString, QString>& pair) : m_Extension(pair.first), m_Version(pair.second)
{
}

const QString& CrosswordFormat::getVersion() const
{
    return m_Version;
}

const QString& CrosswordFormat::getExtension() const
{
    return m_Extension;
}

const QMap<QString, FormatEnum> get2DFormats()
{
    QMap<QString, FormatEnum> map;

    map.insert("xwc", FormatEnum::XWC);
    map.insert("puz", FormatEnum::PUZ);
    map.insert("ccw", FormatEnum::CCW);
    map.insert("cc4", FormatEnum::CC4);

    return map;
}

const QMap<QString, FormatEnum> get3DFormats()
{
    QMap<QString, FormatEnum> map;

    map.insert("xwc3d", FormatEnum::XWC3D);
    map.insert("xwc3dr", FormatEnum::XWC3DR);

    return map;
}

const QMap<QString, FormatEnum> getAllFormats()
{
    QMap<QString, FormatEnum> map = get2DFormats();
    map.unite(get3DFormats());

    return map;
}

}
}
