#include "removetestsuite.h"

#include <qwebdav.h>
#include <qwebdavitem.h>

#include <QFile>
#include <QIODevice>
#include <QSignalSpy>

const int DEFAULT_WAIT_TIMEOUT = 5000;

RemoveTestSuite::RemoveTestSuite(QString host, QString root, QString username, QString password, int port,
                                 QObject *parent)
    : WebDAVBaseSuite(host, root, username, password, port, parent)
{

}

void RemoveTestSuite::remove()
{
    // Put file to remove
    QString path("/removeme.pdf");
    {
        QFile testData(QLatin1String(":/data/rfc4918.pdf"));
        Q_ASSERT(testData.open(QIODevice::ReadOnly));
        QNetworkReply *reply = m_webdav.put(path, &testData);
        QSignalSpy errorSignal(reply, SIGNAL(error(QNetworkReply::NetworkError)));
        QSignalSpy finishedSignal(reply, SIGNAL(finished()));
        QVERIFY(finishedSignal.wait(DEFAULT_WAIT_TIMEOUT));
        QCOMPARE(errorSignal.count(), 0);
        reply->deleteLater();
    }
    // Remove uploaded file
    {
        QNetworkReply *reply = m_webdav.remove(path);
        QSignalSpy errorSignal(reply, SIGNAL(error(QNetworkReply::NetworkError)));
        QSignalSpy finishedSignal(reply, SIGNAL(finished()));
        QVERIFY(finishedSignal.wait(DEFAULT_WAIT_TIMEOUT));
        QCOMPARE(errorSignal.count(), 0);
        reply->deleteLater();
    }
}
