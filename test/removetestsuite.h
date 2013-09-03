#ifndef REMOVETESTSUITE_H
#define REMOVETESTSUITE_H

#include "webdavbasesuite.h"

#include <QtTest/QTest>

class RemoveTestSuite : public WebDAVBaseSuite
{
    Q_OBJECT
public:
    explicit RemoveTestSuite(QString host, QString root, QString username, QString password ,
                             int port, QObject *parent = 0);
    
signals:
    
private slots:
    void remove();

private:

};

#endif // REMOVETESTSUITE_H
