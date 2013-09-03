QT += core network xml testlib
QT -= gui

QMAKE_CXXFLAGS_DEBUG += -std=c++11
QMAKE_CXXFLAGS_RELEASE += -std=c++11

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
    mkdirtestsuite.cpp

win32:CONFIG(release, debug|release) {
    # WINDOWS RELEASE
    PRE_TARGETDEPS += $$OUT_PWD/../qwebdavlib/release/qwebdav.lib
    INCLUDEPATH += $$PWD/../qwebdavlib/
    LIBS += -L$$OUT_PWD/../qwebdavlib/release/ -lqwebdav
} else:win32:CONFIG(debug, debug|release) {
    # WINDOWS DEBUG
    PRE_TARGETDEPS += $$OUT_PWD/../qwebdavlib/debug/qwebdav.lib
    INCLUDEPATH += $$PWD/../qwebdavlib/
    LIBS += -L$$OUT_PWD/../qwebdavlib/debug/ -lqwebdav
}

HEADERS += \
    cmdlineparser.h \
    puttestsuite.h \
    removetestsuite.h \
    webdavbasesuite.h \
    mkdirtestsuite.h

RESOURCES += \
    testdata.qrc

