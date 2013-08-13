#include "crosswordloadingtest.h"

#include <QTest>
#include <QDebug>

#include "testcommon.h"

#include "utilities.h"
#include "crosswordloader.h"

namespace Tests
{

void CrosswordLoadingTest::initTestCase()
{
}

QStringList CrosswordLoadingTest::getTestDataFilepaths(QString dirPath)
{
    QDir testDataDir(dirPath);

    auto files = Utilities::getFilenamesInDirectory(testDataDir);

    if(files.empty())
    {
        qWarning() << "No test files found";
    }
    else
    {
        qDebug() << QString("%1 test files found").arg(files.size());
    }

    return files;
}

void CrosswordLoadingTest::loadValidCrosswords()
{
    auto files = getTestDataFilepaths(Tests::getRegularCrosswordTestPath());

    for(auto& file : files)
    {
        auto supported = m_FormatSupport.isLoaderSupported(file);
        QVERIFY(supported);

        auto loader = m_FormatSupport.locateLoader(file);
        auto loadSuccess = loader->load(file, m_State);
        QVERIFY2(loadSuccess, qPrintable(QString("Failed to load regular crossword: %1").arg(file)));
    }
}

void CrosswordLoadingTest::loadUnusualCrosswords()
{
    auto files = getTestDataFilepaths(Tests::getUnusualCrosswordTestPath());

    for(auto& file : files)
    {
        auto supported = m_FormatSupport.isLoaderSupported(file);
        QVERIFY(supported);

        auto loader = m_FormatSupport.locateLoader(file);
        auto loadSuccess = loader->load(file, m_State);
        QVERIFY2(loadSuccess, qPrintable(QString("Failed to load unusual crossword: %1").arg(file)));
    }
}

void CrosswordLoadingTest::loadBrokenCrosswords()
{
    auto files = getTestDataFilepaths(Tests::getBrokenCrosswordTestPath());

    for(auto& file : files)
    {
        auto supported = m_FormatSupport.isLoaderSupported(file);
        QVERIFY(supported);

        auto loader = m_FormatSupport.locateLoader(file);
        auto loadSuccess = loader->load(file, m_State);
        QVERIFY2(!loadSuccess, qPrintable(QString("Loaded broken crossword: %1").arg(file)));
    }
}

void CrosswordLoadingTest::loadInvalidFiles()
{
    auto files = getTestDataFilepaths(Tests::getInvalidCrosswordTestPath());

    for(auto& file : files)
    {
        auto supported = m_FormatSupport.isLoaderSupported(file);

        QVERIFY2(!supported, qPrintable(QString("Erroneously identified file as a supported file format: %1").arg(file)));
    }
}

void CrosswordLoadingTest::cleanupTestCase()
{
}

}
