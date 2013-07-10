#include "crosswordformat.h"

using namespace Crossword::Formats;

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
