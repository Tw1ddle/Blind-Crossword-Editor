#include "crosswordformatsupportlocator.h"

#include "xwcloader.h"
#include "xwcsaver.h"
#include "xwc3dloader.h"
#include "xwc3dsaver.h"
#include "acrosslitetextloader.h"
#include "acrosslitetextsaver.h"
#include "plaintextsaver.h"

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

const QStringList CrosswordFormatSupportLocator::getSupportedLoadingExtensions() const
{
    QStringList extensions;
    for(auto format : m_Loaders.keys())
    {
        extensions.append(format->getExtension());
    }

    return extensions;
}

const QStringList CrosswordFormatSupportLocator::getSupportedSavingExtensions() const
{
    // This may need refactoring if we need to be able to save to specific versions of a format
    QStringList extensions;
    for(auto format : m_Savers.keys())
    {
        extensions.append(format->getExtension());
    }

    return extensions;
}

void CrosswordFormatSupportLocator::registerFormats()
{
    // Load and save XWC files (v1.0.1)
    registerLoader(new CrosswordFormat(XWC101), new XWCLoader());
    registerSaver(new CrosswordFormat(XWC101), new XWCSaver());

    // Load and save XWC3D files (v1.0.0)
    registerLoader(new CrosswordFormat(XWC3D100), new XWC3DLoader());
    registerSaver(new CrosswordFormat(XWC3D100), new XWC3DSaver());

    // Across Lite Text support
    registerLoader(new CrosswordFormat(ACROSSLITETEXT), new AcrossLiteTextLoader());
    registerSaver(new CrosswordFormat(ACROSSLITETEXT), new AcrossLiteTextSaver());

    // TODO More file support... could scan a directory for .dlls or something
}
