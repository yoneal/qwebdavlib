#ifndef MKDIRTESTSUITE_H
#define MKDIRTESTSUITE_H

#include "webdavbasesuite.h"

#include <QtTest/QTest>

class MkdirTestSuite : public WebDAVBaseSuite
{
    Q_OBJECT
public:
    explicit MkdirTestSuite(QString host, QString root, QString username, QString password ,
                   int port, QObject *parent = 0);

private slots:
    void init();
    void mkdir();
};

#endif // MKDIRTESTSUITE_H
