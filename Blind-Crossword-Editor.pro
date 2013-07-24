TEMPLATE = app

QT += core gui widgets printsupport

CONFIG += x86 x86_64

# Define application metadata
VERSION = 0.1.0
QMAKE_TARGET_PRODUCT = "Blind Crossword Editor"
QMAKE_TARGET_DESCRIPTION = "An accessible 2D and 3D crossword editor"
QMAKE_TARGET_COMPANY = "3D Crosswords Limited"
QMAKE_TARGET_COPYRIGHT = "Copyright 2013"

# Additional languages
TRANSLATIONS += blind-crossword-editor_de.ts

# Pass macros to the main program with application metadata
DEFINES += \
    APP_VERSION=\"\\\"$$VERSION\\\"\" \
    APP_NAME=\"\\\"$$QMAKE_TARGET_PRODUCT\\\"\" \
    APP_DESCRIPTION=\"\\\"$$QMAKE_TARGET_DESCRIPTION\\\"\" \
    APP_ORGANIZATION=\"\\\"$$QMAKE_TARGET_COMPANY\\\"\" \
    APP_COPYRIGHT=\"\\\"$$QMAKE_TARGET_COPYRIGHT\\\"\"

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
    src/recentfilemanager.h

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
    src/recentfilemanager.cpp

FORMS += \
    ui/mainwindow.ui \
    ui/newcrosswordform.ui

RESOURCES += \
    res/resources.qrc

win32
{
    # Specify extra compiler flags
    # Treat all warnings as errors
    QMAKE_CXXFLAGS += /WX

    # Add files so Windows can find the application icon, set executable details etc
    RC_FILE = res/winresources.rc
    OTHER_FILES += res/winresources.rc
}
