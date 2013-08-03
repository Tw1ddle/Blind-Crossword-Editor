TEMPLATE = app

QT += core gui widgets printsupport

CONFIG += x86 x86_64

# Specify extra compiler flags

# For msvc
win32-msvc* {
    # Increase warning level
    QMAKE_CXXFLAGS_WARN_ON -= -W3
    QMAKE_CXXFLAGS_WARN_ON += -W4

    # Silence some known Qt warnings
    QMAKE_CXXFLAGS += -wd4127 -wd4512 -wd4189

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
QMAKE_TARGET_DESCRIPTION = "An accessible 2D and 3D crossword editor"
QMAKE_TARGET_COMPANY = "3D Crosswords Limited"
QMAKE_TARGET_COPYRIGHT = "Copyright 2013"

# Additional languages
TRANSLATIONS += blind-crossword-editor_de.ts

# Pass macros to the C preprocessor with the application metadata
DEFINES += \
    APP_VERSION=\"\\\"$$VERSION\\\"\" \
    APP_NAME=\"\\\"$$QMAKE_TARGET_PRODUCT\\\"\" \
    APP_DESCRIPTION=\"\\\"$$QMAKE_TARGET_DESCRIPTION\\\"\" \
    APP_ORGANIZATION=\"\\\"$$QMAKE_TARGET_COMPANY\\\"\" \
    APP_COPYRIGHT=\"\\\"$$QMAKE_TARGET_COPYRIGHT\\\"\" \

DEFINES += \
    APP_COMPILER_NAME=\"\\\"$$QMAKE_CXX\\\"\"

HEADERS += \
    src/crosswordstate.h \
    src/crosswordbase.h \
    src/mainwindow.h \
    src/crosswordsaver.h \
    src/crosswordloader.h \
    src/appinfo.h \
    src/appsettings.h \
    src/gridscene.h \
    src/griditem.h \
    src/gridview.h \
    src/vectormath.h \
    src/crosswordformatsupportlocator.h \
    src/xwcloader.h \
    src/xwcsaver.h \
    src/crosswordformat.h \
    src/gridsquare.h \
    src/recentfilemanager.h \
    src/crosswordclue.h \
    src/utilities.h \
    src/xwccommon.h \
    src/xwc3dloader.h \
    src/xwc3dsaver.h \
    src/xwc3dcommon.h \
    src/crossworditem.h \
    src/gridscene2d.h \
    src/gridscene3d.h \
    src/gridscenecombinationlock.h \
    src/gridscenerectangularlayers.h \
    src/internalinterfaces.h \
    src/logginghandler.h \
    src/aboutpage.h \
    src/licensepage.h \
    src/crosswordstatisticspage.h \
    src/autoupdater.h \
    ui/contributorspage.h \
    src/contributorspage.h

SOURCES += \
    src/crosswordstate.cpp \
    src/crosswordbase.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/crosswordsaver.cpp \
    src/crosswordloader.cpp \
    src/appsettings.cpp \
    src/gridscene.cpp \
    src/griditem.cpp \
    src/gridview.cpp \
    src/crosswordformatsupportlocator.cpp \
    src/xwcloader.cpp \
    src/xwcsaver.cpp \
    src/crosswordformat.cpp \
    src/gridsquare.cpp \
    src/recentfilemanager.cpp \
    src/crosswordclue.cpp \
    src/utilities.cpp \
    src/xwccommon.cpp \
    src/xwc3dloader.cpp \
    src/xwc3dsaver.cpp \
    src/xwc3dcommon.cpp \
    src/crossworditem.cpp \
    src/gridscene2d.cpp \
    src/gridscene3d.cpp \
    src/gridscenecombinationlock.cpp \
    src/gridscenerectangularlayers.cpp \
    src/logginghandler.cpp \
    src/aboutpage.cpp \
    src/licensepage.cpp \
    src/crosswordstatisticspage.cpp \
    src/autoupdater.cpp \
    src/contributorspage.cpp

FORMS += \
    ui/mainwindow.ui \
    ui/newcrosswordform.ui \
    ui/griditempropertiesform.ui \
    ui/aboutpage.ui \
    ui/licensepage.ui \
    ui/crosswordstatisticspage.ui \
    ui/contributorspage.ui

RESOURCES += \
    res/resources.qrc
