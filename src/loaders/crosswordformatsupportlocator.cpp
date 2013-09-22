#include "crosswordformatsupportlocator.h"

#include <QtAlgorithms>
#include <QFileInfo>
#include <QStringList>

using namespace Crossword;
using namespace Crossword::Formats;

CrosswordFormatSupportLocator::CrosswordFormatSupportLocator()
{
}

CrosswordFormatSupportLocator::~CrosswordFormatSupportLocator()
{
    // TODO C4718 QMapMode... compiler error was preventing this from building in release mode (till I disabled the warning)
    // ... look into it
    qDeleteAll(m_Loaders);
    m_Loaders.clear();

    qDeleteAll(m_Savers);
    m_Savers.clear();
}

const CrosswordLoader* CrosswordFormatSupportLocator::locateLoader(const CrosswordFormat& format) const
{
    return locate(m_Loaders, format);
}

const CrosswordSaver* CrosswordFormatSupportLocator::locateSaver(const CrosswordFormat& format) const
{
    return locate(m_Savers, format);
}

const CrosswordLoader* CrosswordFormatSupportLocator::locateLoader(const QString& filepath) const
{
    return locate(m_Loaders, filepath);
}

const CrosswordSaver* CrosswordFormatSupportLocator::locateSaver(const QString& filepath) const
{
    return locate(m_Savers, filepath);
}

void CrosswordFormatSupportLocator::registerLoader(CrosswordFormat* format, CrosswordLoader* loader)
{
    m_Loaders.insert(format, loader);
}

void CrosswordFormatSupportLocator::registerSaver(CrosswordFormat* format, CrosswordSaver* saver)
{
    m_Savers.insert(format, saver);
}

bool CrosswordFormatSupportLocator::isLoaderSupported(const CrosswordFormat& format) const
{
    return isSupported(m_Loaders, format);
}

bool CrosswordFormatSupportLocator::isSaverSupported(const CrosswordFormat& format) const
{
    return isSupported(m_Savers, format);
}

bool CrosswordFormatSupportLocator::isLoaderSupported(const QString& filepath) const
{
    return (nullptr != locate(m_Loaders, filepath));
}

bool CrosswordFormatSupportLocator::isSaverSupported(const QString& filepath) const
{
    return (nullptr != locate(m_Savers, filepath));
}

const QString CrosswordFormatSupportLocator::getExtension(const QString& filepath) const
{
    QFileInfo info(filepath);

    return info.suffix();
}

const QStringList CrosswordFormatSupportLocator::getSupportedLoadingExtensions() const
{
    QStringList extensions;
    auto keys = m_Loaders.keys();
    for(auto format : keys)
    {
        extensions.append(format->getExtension());
    }

    return extensions;
}

const QStringList CrosswordFormatSupportLocator::getSupportedSavingExtensions() const
{
    // This may need refactoring if we need to be able to save to specific versions of a format
    QStringList extensions;

    auto keys = m_Savers.keys();
    for(auto format : keys)
    {
        extensions.append(format->getExtension());
    }

    return extensions;
}
