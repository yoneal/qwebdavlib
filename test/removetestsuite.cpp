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
    QWebdav w;
    // Put file to remove
    w.setConnectionSettings(QWebdav::HTTP, m_hostname, m_root, m_username, m_password, m_port);
    QString path("/removeme.pdf");
    {
        QFile testData(QLatin1String(":/data/rfc4918.pdf"));
        Q_ASSERT(testData.open(QIODevice::ReadOnly));
        QNetworkReply *reply = w.put(path, &testData);
        QSignalSpy errorSignal(reply, SIGNAL(error(QNetworkReply::NetworkError)));
        QSignalSpy finishedSignal(reply, SIGNAL(finished()));
        QVERIFY(finishedSignal.wait(DEFAULT_WAIT_TIMEOUT));
        QCOMPARE(errorSignal.count(), 0);
        reply->deleteLater();
    }
    // Remove uploaded file
    {
        QNetworkReply *reply = w.remove(path);
        QSignalSpy errorSignal(reply, SIGNAL(error(QNetworkReply::NetworkError)));
        QSignalSpy finishedSignal(reply, SIGNAL(finished()));
        QVERIFY(finishedSignal.wait(DEFAULT_WAIT_TIMEOUT));
        QCOMPARE(errorSignal.count(), 0);
        reply->deleteLater();
    }
}
