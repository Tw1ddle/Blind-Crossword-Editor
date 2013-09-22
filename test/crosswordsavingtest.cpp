#include "crosswordsavingtest.h"

#include <QDebug>
#include <QTest>

#include "utilities.h"
#include "testcommon.h"
#include "crosswordformat.h"

namespace Tests
{

void CrosswordSavingTest::initTestCase()
{
}

void CrosswordSavingTest::cleanupTestCase()
{
}

void CrosswordSavingTest::saveToSupportedFormats()
{
    auto filepaths = getTestDataFilepaths(getRegularCrosswordTestPath());

    for(auto& filepath : filepaths)
    {
        Crossword::CrosswordState state;
        bool loaded = loadFile(state, filepath);

        auto filename = getFilenameForFilepath(filepath);

        if(loaded)
        {
            auto formats = m_FormatSupport.getSupportedSavingExtensions();
            for(auto& format : formats)
            {
                testSaveFile(state, filename, format);
            }
        }
    }
}

void Tests::CrosswordSavingTest::testSaveFile(const Crossword::CrosswordState& state, const QString& filename, const QString& extension)
{
    QVERIFY2(!(saveFile(state, extension).isEmpty()),
             qPrintable(QString("Failed to save file %1 as %2").arg(filename, extension)));
}

void CrosswordSavingTest::checkEquivalence()
{
    qDebug() << qPrintable(QString("Begin checking save equivalence"));

    auto filepaths = getTestDataFilepaths(getRegularCrosswordTestPath());

    // Save each file to its original format, reload the saves, and find the differences (if any)
    for(int i = 0; i < filepaths.size(); i++)
    {
        auto filepath = filepaths.at(i);
        auto filename = getFilenameForFilepath(filepath);

        const auto& extension = m_FormatSupport.getExtension(filepath);
        const auto& loader = m_FormatSupport.locateLoader(filepath);

        if(!loader)
        {
            qDebug() << qPrintable(QString("File %1, %2 - Unsupported format: %3").arg(QString::number(i), filename, extension));
            continue;
        }
        else
        {
            qDebug() << qPrintable(QString("File %1, %2").arg(QString::number(i), filename));
        }

        // Load file lines, write into a file using a loader, then read back out and compare
        QStringList firstLines = Utilities::readFile(filepath);

        if(loader)
        {
            Crossword::CrosswordState firstState = loader->load(firstLines);
            firstState.m_DataSources.m_PuzzleFilePath = filepath; // Remember to set filepath as loading from stringlist does not do that

            QStringList secondLines = saveFile(firstState, extension);
            checkEquivalent(firstLines, secondLines);
        }
    }

    qDebug() << qPrintable(QString("End checking save equivalence"));
}

// Files need loading before we can resave them
bool CrosswordSavingTest::loadFile(Crossword::CrosswordState& state, const QString& filepath)
{
    auto loader = m_FormatSupport.locateLoader(filepath);

    if(nullptr == loader)
    {
        return false;
    }

    bool success = loader->load(filepath, state);

    return success;
}

QStringList CrosswordSavingTest::saveFile(const Crossword::CrosswordState& state, const QString& extension)
{
    QString filename = Tests::getFilenameForFilepath(state.m_DataSources.m_PuzzleFilePath);

    auto saver = m_FormatSupport.locateSaver(extension);

    if(nullptr == saver)
    {
        qDebug() << qPrintable(QString("No support for %1 as %2").arg(filename, m_FormatSupport.getExtension(extension)));

        return QStringList();
    }

    auto lines = saver->save(state);

    if(lines.empty())
    {
        qDebug() << qPrintable(QString("Saving failed"));
    }

    return lines;
}

void CrosswordSavingTest::checkEquivalent(const QStringList& first, const QStringList& second)
{
    bool empty = first.empty() || second.empty();

    QVERIFY2(!empty, qPrintable(QString("One or more empty files")));

    bool equalLengths = first.length() == second.length();

    if(!equalLengths)
    {
        qDebug() << qPrintable(QString("File lengths differ, %1 vs %2").arg
                               (QString::number(first.length()),
                                QString::number(second.length())));
    }

    /*
    QVERIFY2(equalLengths, qPrintable(
                 QString("File lengths differ, %1 vs %2").arg
                 (QString::number(first.length()),
                  QString::number(second.length()))));
    */

    int minLength = std::min(first.length(), second.length());
    bool equivalent = true;
    int differences = 0;

    for(int i = 0; i < minLength; i++)
    {
        bool equivalentLines = first.at(i) == second.at(i);

        if(!equivalentLines)
        {
            differences++;
            equivalent = false;
            qDebug() << qPrintable(QString("Line %1 differs : \n [%2] \n [%3]").arg(QString::number(i), first.at(i), second.at(i)));
        }

        if(differences > m_MaxNumDifferences)
        {
            qDebug() << qPrintable(QString("Maximum of %1 differences exceeded").arg(QString::number(m_MaxNumDifferences)));
            i = minLength;
        }
    }

    QVERIFY2(equivalent, qPrintable(QString("Files were not equivalent")));
}

}
