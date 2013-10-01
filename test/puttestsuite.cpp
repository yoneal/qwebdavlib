#include "puttestsuite.h"

#include <qwebdav.h>
#include <qwebdavitem.h>

#include <QFile>
#include <QIODevice>
#include <QSignalSpy>

const int DEFAULT_WAIT_TIMEOUT = 5000;

PutTestSuite::PutTestSuite(QString host, QString root, QString username, QString password, int port,
                           QObject *parent)
    : WebDAVBaseSuite(host, root, username, password, port, parent)
{

}

void PutTestSuite::putIODevice()
{
    QString path("/putIODevice.pdf");
    QFile testData(QLatin1String(":/data/earth_art.pdf"));
    Q_ASSERT(testData.open(QIODevice::ReadOnly));
    QNetworkReply *reply = m_webdav.put(path, dynamic_cast<QIODevice*>(&testData));
    QSignalSpy errorSignal(reply, SIGNAL(error(QNetworkReply::NetworkError)));
    QSignalSpy finishedSignal(reply, SIGNAL(finished()));

    QVERIFY(finishedSignal.wait(DEFAULT_WAIT_TIMEOUT));
    QCOMPARE(errorSignal.count(), 0);
    reply->deleteLater();
}

void PutTestSuite::putByteArray()
{
    QString path("/putByteArray.pdf");
    QFile testData(QLatin1String(":/data/rfc4918.pdf"));
    Q_ASSERT(testData.open(QIODevice::ReadOnly));
    QByteArray data = testData.readAll();
    QNetworkReply *reply = m_webdav.put(path, data);
    QSignalSpy errorSignal(reply, SIGNAL(error(QNetworkReply::NetworkError)));
    QSignalSpy finishedSignal(reply, SIGNAL(finished()));

    QVERIFY(finishedSignal.wait(DEFAULT_WAIT_TIMEOUT));
    QCOMPARE(errorSignal.count(), 0);
    reply->deleteLater();
}
