# Code that pertains to loading, saving, exporting etc of crosswords

INCLUDEPATH += $$PWD

HEADERS += \
    src/loaders/crosswordloader.h \
    src/loaders/crosswordsaver.h \
    src/loaders/xwc3dloader.h \
    src/loaders/xwc3dsaver.h \
    src/loaders/xwc3dcommon.h \
    src/loaders/xwcloader.h \
    src/loaders/xwcsaver.h \
    src/loaders/xwccommon.h \
    src/loaders/acrosslitetextloader.h \
    src/loaders/acrosslitetextsaver.h \
    src/loaders/acrosslitetextcommon.h \
    src/loaders/webglsaver.h \
    src/loaders/xmlsaver.h \
    src/loaders/plaintextsaver.h \
    src/loaders/formatscommon.h \
    src/loaders/exporters.h \
    src/loaders/crosswordformat.h \
    src/loaders/crosswordformatsupportlocator.h \
    src/loaders/crosswordexportsupportlocator.h \
    src/loaders/crosswordloadsupportlocator.h

SOURCES += \
    src/loaders/crosswordloader.cpp \
    src/loaders/crosswordsaver.cpp \
    src/loaders/xwc3dloader.cpp \
    src/loaders/xwc3dsaver.cpp \
    src/loaders/xwc3dcommon.cpp \
    src/loaders/xwcloader.cpp \
    src/loaders/xwcsaver.cpp \
    src/loaders/xwccommon.cpp \
    src/loaders/acrosslitetextloader.cpp \
    src/loaders/acrosslitetextsaver.cpp \
    src/loaders/acrosslitetextcommon.cpp \
    src/loaders/webglsaver.cpp \
    src/loaders/xmlsaver.cpp \
    src/loaders/plaintextsaver.cpp \
    src/loaders/formatscommon.cpp \
    src/loaders/exporters.cpp \
    src/loaders/crosswordformat.cpp \
    src/loaders/crosswordformatsupportlocator.cpp \
    src/loaders/crosswordexportsupportlocator.cpp \
    src/loaders/crosswordloadsupportlocator.cpp
