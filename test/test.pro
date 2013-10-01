QT += core network xml testlib
QT -= gui

!win32-msvc2010 {
    QMAKE_CXXFLAGS_DEBUG += -std=c++11
    QMAKE_CXXFLAGS_RELEASE += -std=c++11
}

TARGET = tester
CONFIG += console
#CONFIG -= app_bundle

TEMPLATE = app

# Enable extended WebDAV properties (see QWebDavItem.h/cpp)
DEFINES += QWEBDAVITEM_EXTENDED_PROPERTIES

SOURCES += \
    main.cpp \
    cmdlineparser.cpp \
    puttestsuite.cpp \
    removetestsuite.cpp \
    webdavbasesuite.cpp \
    mkdirtestsuite.cpp \
    testrunner.cpp \
    gettestsuite.cpp

win32:CONFIG(release, debug|release) {
    # WINDOWS RELEASE
    PRE_TARGETDEPS += $$OUT_PWD/../qwebdavlib/release/qwebdav.dll
    INCLUDEPATH += $$PWD/../qwebdavlib/
    LIBS += -L$$OUT_PWD/../qwebdavlib/release/ -lqwebdav
} else:win32:CONFIG(debug, debug|release) {
    # WINDOWS DEBUG
    PRE_TARGETDEPS += $$OUT_PWD/../qwebdavlib/debug/qwebdav.dll
    INCLUDEPATH += $$PWD/../qwebdavlib/
    LIBS += -L$$OUT_PWD/../qwebdavlib/debug/ -lqwebdav
}

HEADERS += \
    cmdlineparser.h \
    puttestsuite.h \
    removetestsuite.h \
    webdavbasesuite.h \
    mkdirtestsuite.h \
    testrunner.h \
    gettestsuite.h

RESOURCES += \
    testdata.qrc
