#ifndef PUTTESTSUITE_H
#define PUTTESTSUITE_H

#include "webdavbasesuite.h"

#include <QtTest/QTest>
#include <QObject>

class PutTestSuite : public WebDAVBaseSuite
{
    Q_OBJECT
public:
    explicit PutTestSuite(QString host, QString root, QString username, QString password ,
                          int port, QObject *parent = 0);

signals:
    
private slots:
    void putIODevice();
    void putByteArray();

private:

};

#endif // PUTTESTSUITE_H
