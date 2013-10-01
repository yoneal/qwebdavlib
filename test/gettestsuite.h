#ifndef GETTESTSUITE_H
#define GETTESTSUITE_H

#include "webdavbasesuite.h"
#include <QObject>

class GetTestSuite : public WebDAVBaseSuite
{
    Q_OBJECT
public:
    explicit GetTestSuite(QString host, QString root, QString username, QString password ,
                          int port, QObject *parent = 0);

private:
    int  m_testDataSize;

private slots:
    void initTestCase();
    void cleanupTestCase();
    void get();
    void getIODevice();
    void getIODeviceWithRange();
};

#endif // GETTESTSUITE_H
