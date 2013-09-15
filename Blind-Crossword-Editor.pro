TEMPLATE = app

QT += core gui widgets printsupport testlib

CONFIG += x86 x86_64

# Specify extra compiler flags

# For msvc
win32-msvc* {
    # Increase warning level
    QMAKE_CXXFLAGS_WARN_ON -= -W3
    QMAKE_CXXFLAGS_WARN_ON += -W4

    # Silence some known Qt warnings
    QMAKE_CXXFLAGS += -wd4127 -wd4512 -wd4189

    # Silence a warning that popped up concerning the QMap destructor in the crossword format support locator
    QMAKE_CXXFLAGS += -wd4718

    # Treat warnings as errors
    QMAKE_CXXFLAGS += -WX
}

# GCC
*-g++ {
    QMAKE_CXXFLAGS += -std=c++11

    # Lots of warnings, treat warnings as errors
    QMAKE_CXXFLAGS += -Wall -Wextra -pedantic -Werror
}

win32 {
    # Add files so Windows can find the application icon, set executable details etc
    RC_FILE = res/winresources.rc
    OTHER_FILES += res/winresources.rc
}

# Application metadata
VERSION = 0.1.0
QMAKE_TARGET_PRODUCT = "Blind Crossword Editor"
QMAKE_TARGET_DESCRIPTION = "An accessible 2D and 3D crossword editor."
QMAKE_TARGET_COMPANY = "3D Crosswords Limited."
QMAKE_TARGET_COPYRIGHT = "Copyright 2013."

# Pass macros to the C preprocessor with the application metadata
DEFINES += \
    APP_VERSION=\"\\\"$$VERSION\\\"\" \
    APP_NAME=\"\\\"$$QMAKE_TARGET_PRODUCT\\\"\" \
    APP_DESCRIPTION=\"\\\"$$QMAKE_TARGET_DESCRIPTION\\\"\" \
    APP_ORGANIZATION=\"\\\"$$QMAKE_TARGET_COMPANY\\\"\" \
    APP_COPYRIGHT=\"\\\"$$QMAKE_TARGET_COPYRIGHT\\\"\" \

DEFINES += \
    APP_COMPILER_NAME=\"\\\"$$QMAKE_CXX\\\"\"


include(test/tests.pri)
include(lang/lang.pri)
include(src/src.pro)

FORMS += \
    ui/mainwindow.ui \
    ui/griditempropertiesform.ui \
    ui/aboutpage.ui \
    ui/licensepage.ui \
    ui/crosswordstatisticspage.ui \
    ui/contributorspage.ui \
    ui/preferencespage.ui \
    ui/newcrosswordpage.ui \
    ui/newcrosswordcluepage.ui

RESOURCES += \
    res/resources.qrc
