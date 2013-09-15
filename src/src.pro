# Code that pertains to the editor

INCLUDEPATH += $$PWD

include(loaders/loaders.pri)

HEADERS += \
    src/crosswordstate.h \
    src/crosswordbase.h \
    src/mainwindow.h \
    src/appinfo.h \
    src/appsettings.h \
    src/gridscene.h \
    src/griditem.h \
    src/gridview.h \
    src/vectormath.h \
    src/gridsquare.h \
    src/recentfilemanager.h \
    src/crosswordclue.h \
    src/utilities.h \
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
    src/contributorspage.h \
    src/contributorspage.h \
    src/preferencespage.h \
    src/crosswordtemplates.h \
    src/newcrosswordpage.h \
    src/crosswordstatistics.h \
    src/newcrosswordcluepage.h \
    src/gridclue.h \
    src/gridshape.h \
    src/gridfillalgorithm.h \
    src/wordlist.h

SOURCES += \
    src/crosswordstate.cpp \
    src/crosswordbase.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/appsettings.cpp \
    src/gridscene.cpp \
    src/griditem.cpp \
    src/gridview.cpp \
    src/gridsquare.cpp \
    src/recentfilemanager.cpp \
    src/crosswordclue.cpp \
    src/utilities.cpp \
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
    src/contributorspage.cpp \
    src/preferencespage.cpp \
    src/crosswordtemplates.cpp \
    src/newcrosswordpage.cpp \
    src/crosswordstatistics.cpp \
    src/newcrosswordcluepage.cpp \
    src/gridclue.cpp \
    src/gridshape.cpp \
    src/gridfillalgorithm.cpp \
    src/wordlist.cpp
