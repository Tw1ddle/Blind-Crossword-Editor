#ifndef CROSSWORDFORMATSUPPORTLOCATOR_H
#define CROSSWORDFORMATSUPPORTLOCATOR_H

#include <QString>
#include <QStringList>
#include <QMap>
#include <QFileInfo>
#include <tuple>

#include "crosswordformat.h"
#include "crosswordloader.h"
#include "crosswordsaver.h"

namespace Crossword
{

namespace Formats
{

// A registry that is searched to find which crossword file formats are supported
// This has been implemented so that if loading/saving functionality can be abstracted from the rest of the application
class CrosswordFormatSupportLocator
{
public:
    CrosswordFormatSupportLocator();
    ~CrosswordFormatSupportLocator();

    // If these return nullptr then the format support isn't there
    // Once loaders/savers do more complicated work it may be necessary to get rid of the constness
    const CrosswordLoader* locateLoader(const Formats::CrosswordFormat& format) const;
    const CrosswordSaver* locateSaver(const Formats::CrosswordFormat& format) const;

    // Checks whether the format can be loaded or saved
    bool isLoaderSupported(const Formats::CrosswordFormat& format) const;
    bool isSaverSupported(const Formats::CrosswordFormat& format) const;

    // Whether the format extension is supported (takes any kind of filename or path so long)
    // Note this does not check to see if the specific format version is supported

    // This works for extensions alone too, provided that they have the prepended "." e.g. ".xwc"
    const CrosswordLoader* locateLoader(const QString& filepath) const;
    const CrosswordSaver* locateSaver(const QString& filepath) const;

    bool isLoaderSupported(const QString& filepath) const;
    bool isSaverSupported(const QString& filepath) const;


    void registerLoader(Formats::CrosswordFormat* format, CrosswordLoader* loader);
    void registerSaver(Formats::CrosswordFormat* format, CrosswordSaver* saver);

    // Get a list of the supported loading file formats
    // Use case could be to only show files that have loading support in a file dialog
    const QStringList getSupportedLoadingExtensions() const;
    // Get a list of the supported saving file formats
    const QStringList getSupportedSavingExtensions() const;

    // Extract the file extension from a file path
    // Returns all characters after but not including the last '.'
    const QString getExtension(const QString& filepath) const;

private:
    // Generalization for loader/saver calls
    // Just a "find" method
    template<class T, class V>
    bool isSupported(const QMap<const T*, const V*>& map, const T& format) const;

    // Generalization for locate loader/saver calls
    // Another "find" method that returns a supported loader for a format
    template<class T, class V>
    const V* locate(const QMap<const T*, const V*>& map, const T& format) const;

    // Weaker generalization for locate loader/saver calls
    // Has a weaker precondition - returns a loader (which depends on QMap implementation) for which an extension is supported
    // Disregards the version number of the format
    template<class T, class V>
    const V* locate(const QMap<const T*, const V*>& map, const QString& filepath) const;

    // Called on construction, just registers all the supported loaders and savers
    // Might change this later if format support can be extended externally (.dlls etc)
    virtual void registerFormats() = 0;

    // Only one loader or saver should be registered for any particular version of a file format
    QMap<const Formats::CrosswordFormat*, const CrosswordLoader*> m_Loaders;
    QMap<const Formats::CrosswordFormat*, const CrosswordSaver*> m_Savers;
};

template<class T, class V>
const V* CrosswordFormatSupportLocator::locate(const QMap<const T*, const V*>& map, const T& format) const
{
    QList<const T*> keys = map.keys();

    for(auto key : keys)
    {
        if(key->getExtension() == format.getExtension() && key->getVersion() == format.getVersion())
        {
            return map.find(key).value();
        }
    }

    return nullptr;
}

template<class T, class V>
const V* CrosswordFormatSupportLocator::locate(const QMap<const T*, const V*>& map, const QString& filepath) const
{
    QFileInfo file(filepath);

    Q_ASSERT(!file.isDir());

    // If necessary trim the provided filepath to get the file extension
    QString extension = filepath;

    if(!file.suffix().isEmpty())
    {
        extension = getExtension(filepath);
    }

    QList<const T*> keys = map.keys();

    for(auto key : keys)
    {
        if(key->getExtension() == extension)
        {
            return map.find(key).value();
        }
    }

    return nullptr;
}

template<class T, class V>
bool CrosswordFormatSupportLocator::isSupported(const QMap<const T*, const V*>& map, const T& format) const
{
    return (nullptr != locate(map, format));
}

}

}

#endif // CROSSWORDFORMATSUPPORTLOCATOR_H
