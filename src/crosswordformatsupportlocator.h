#ifndef CROSSWORDFORMATSUPPORTLOCATOR_H
#define CROSSWORDFORMATSUPPORTLOCATOR_H

#include <QString>
#include <QStringList>
#include <QMap>
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
    const CrosswordLoader* const locateLoader(const Formats::CrosswordFormat& format) const;
    const CrosswordSaver* const locateSaver(const Formats::CrosswordFormat& format) const;

    // Checks whether the format can be loaded or saved
    bool isLoaderSupported(const Formats::CrosswordFormat& format) const;
    bool isSaverSupported(const Formats::CrosswordFormat& format) const;

    // Whether the format extension is supported (takes any kind of filename or path so long)
    // Note this does not check to see if the specific format version is supported
    const CrosswordLoader* const locateLoader(const QString& filepath) const;
    const CrosswordSaver* const locateSaver(const QString& filepath) const;

    bool isLoaderSupported(const QString& filepath) const;
    bool isSaverSupported(const QString& filepath) const;


    void registerLoader(Formats::CrosswordFormat* format, CrosswordLoader* loader);
    void registerSaver(Formats::CrosswordFormat* format, CrosswordSaver* saver);

    // Extract the file extension from a file path
    // Returns all characters after but not including the last '.'
    const QString getExtension(const QString& filepath) const;


    // Get a list of the supported loading file formats
    // Use case could be to only show files that have loading support in a file dialog
    const QStringList getSupportedLoadingExtensions() const;
    // Get a list of the supported saving file formats
    const QStringList getSupportedSavingExtensions() const;

private:
    // Generalization for loader/saver calls
    // Just a "find" method
    template<class T, class V>
    bool isSupported(const QMap<const T*, const V*>& map, const T& format) const;

    // Generalization for locate loader/saver calls
    // Another "find" method that returns a supported loader for a format
    template<class T, class V>
    const V* const locate(const QMap<const T*, const V*>& map, const T& format) const;

    // Weaker generalization for locate loader/saver calls
    // Has a weaker precondition - returns a loader (which depends on QMap implementation) for which an extension is supported
    // Disregards the version number of the format
    template<class T, class V>
    const V* const locate(const QMap<const T*, const V*>& map, const QString& filepath) const;

    // Called on construction, just registers all the supported loaders and savers
    // Might change this later if format support can be extended externally (.dlls etc)
    void registerFormats();

    // Only one loader or saver should be registered for any particular version of a file format
    QMap<const Formats::CrosswordFormat*, const CrosswordLoader*> m_Loaders;
    QMap<const Formats::CrosswordFormat*, const CrosswordSaver*> m_Savers;
};

template<class T, class V>
const V* const CrosswordFormatSupportLocator::locate(const QMap<const T*, const V*>& map, const T& format) const
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
const V* const CrosswordFormatSupportLocator::locate(const QMap<const T*, const V*>& map, const QString& filepath) const
{
    QList<const T*> keys = map.keys();

    // Trim the provided filepath to get the file extension
    const QString extension = this->getExtension(filepath);

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
    return (locate(map, format) != nullptr);
}

}

}

#endif // CROSSWORDFORMATSUPPORTLOCATOR_H
