#include "crosswordformatsupportlocator.h"

#include "xwcloader.h"
#include "xwcsaver.h"

#include <QtAlgorithms>
#include <QFileInfo>
#include <QStringList>

using namespace Crossword;
using namespace Crossword::Formats;

CrosswordFormatSupportLocator::CrosswordFormatSupportLocator()
{
    // Register all the supported formats here (temporarily)
    registerFormats();
}

CrosswordFormatSupportLocator::~CrosswordFormatSupportLocator()
{
    qDeleteAll(m_Loaders);
    m_Loaders.clear();

    qDeleteAll(m_Savers);
    m_Savers.clear();
}

const CrosswordLoader* const CrosswordFormatSupportLocator::locateLoader(const CrosswordFormat& format) const
{
    return locate(m_Loaders, format);
}

const CrosswordSaver* const CrosswordFormatSupportLocator::locateSaver(const CrosswordFormat& format) const
{
    return locate(m_Savers, format);
}

const CrosswordLoader* const CrosswordFormatSupportLocator::locateLoader(const QString& filepath) const
{
    return locate(m_Loaders, filepath);
}

const CrosswordSaver* const CrosswordFormatSupportLocator::locateSaver(const QString& filepath) const
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
    return locate(m_Loaders, filepath);
}

bool CrosswordFormatSupportLocator::isSaverSupported(const QString& filepath) const
{
    return locate(m_Savers, filepath);
}

const QString CrosswordFormatSupportLocator::getExtension(const QString& filepath) const
{
    QFileInfo info(filepath);

    return info.suffix();
}

const QString CrosswordFormatSupportLocator::getSupportedLoadingFormatFilter() const
{
    QStringList extensions;
    for(auto format : m_Loaders.keys())
    {
        extensions.append(format->getExtension());
    }

    QString filter;
    // TODO

    return filter;
}

const QString CrosswordFormatSupportLocator::getSupportedSavingFormatFilter() const
{
    QStringList extensions;
    for(auto format : m_Savers.keys())
    {
        extensions.append(format->getExtension());
    }

    QString filter;
    // TODO

    return filter;
}

void CrosswordFormatSupportLocator::registerFormats()
{
    // Load and save XWC files (v1.01)
    registerLoader(new CrosswordFormat(XWC101), new XWCLoader());
    registerSaver(new CrosswordFormat(XWC101), new XWCSaver());

    // TODO More file support... could scan a directory for .dlls or something
}
