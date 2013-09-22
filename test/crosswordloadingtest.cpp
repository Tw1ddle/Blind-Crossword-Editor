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

void CrosswordLoadingTest::loadValidCrosswords()
{
    bool success = loadCrosswords(Tests::getRegularCrosswordTestPath());

    QVERIFY2(success, "Regular crosswords failed to load");
}

void CrosswordLoadingTest::loadUnusualCrosswords()
{
    bool success = loadCrosswords(Tests::getUnusualCrosswordTestPath());

    QVERIFY2(success, "Unusual crosswords failed to load");
}

void CrosswordLoadingTest::loadBrokenCrosswords()
{
    bool success = loadCrosswords(Tests::getBrokenCrosswordTestPath());

    QVERIFY2(!success, "Broken crosswords loaded anyway");
}

void CrosswordLoadingTest::loadInvalidFiles()
{
    bool success = loadCrosswords(Tests::getInvalidCrosswordTestPath());

    QVERIFY2(!success, "Invalid crosswords loaded");
}

bool CrosswordLoadingTest::loadCrosswords(QString testPath)
{
    auto files = getTestDataFilepaths(testPath);

    bool allSuccessful = true;
    for(auto& file : files)
    {
        QString filename = Tests::getFilenameForFilepath(file);

        if(auto loader = m_FormatSupport.locateLoader(file))
        {
            if(loader->load(file, m_State))
            {
            }
            else
            {
                qDebug() << qPrintable(QString("Crossword failed to load: %1").arg(filename));
                allSuccessful = false;
            }
        }
        else
        {
            qDebug() << qPrintable(QString("Unsupported format for file: %1").arg(filename));
            allSuccessful = false;
        }
    }

    return allSuccessful;
}

void CrosswordLoadingTest::cleanupTestCase()
{
}

}
