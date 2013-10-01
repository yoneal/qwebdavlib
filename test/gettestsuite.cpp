#include "gettestsuite.h"

#include <qwebdav.h>

#include <QFile>
#include <QIODevice>
#include <QSignalSpy>
#include <QtTest/QTest>
#include <QTemporaryFile>

const int DEFAULT_WAIT_TIMEOUT = 5000;
const QString testDataPath("/getTestData.pdf");

GetTestSuite::GetTestSuite(QString host, QString root, QString username, QString password, int port,
                           QObject *parent)
    : WebDAVBaseSuite(host, root, username, password, port, parent)
{

}

void GetTestSuite::initTestCase()
{
    WebDAVBaseSuite::initTestCase();
    QFile testData(QLatin1String(":/data/rfc4918.pdf"));
    Q_ASSERT(testData.open(QIODevice::ReadOnly));
    QByteArray data = testData.readAll();
    m_testDataSize = data.size();
    QNetworkReply *reply = m_webdav.put(testDataPath, data);
    QSignalSpy finishedSignal(reply, SIGNAL(finished()));
    QVERIFY(finishedSignal.wait(DEFAULT_WAIT_TIMEOUT));
    reply->deleteLater();
}

void GetTestSuite::cleanupTestCase()
{
    QNetworkReply *reply = m_webdav.remove(testDataPath);
    QSignalSpy finishedSignal(reply, SIGNAL(finished()));
    QVERIFY(finishedSignal.wait(DEFAULT_WAIT_TIMEOUT));
    reply->deleteLater();
}

void GetTestSuite::get()
{
    QNetworkReply *reply = m_webdav.get(testDataPath);
    QSignalSpy errorSignal(reply, SIGNAL(error(QNetworkReply::NetworkError)));
    QSignalSpy readSignal(reply, SIGNAL(readyRead()));
    QSignalSpy finishedSignal(reply, SIGNAL(finished()));

    QVERIFY(finishedSignal.wait(DEFAULT_WAIT_TIMEOUT));
    QCOMPARE(errorSignal.count(), 0);
    QVERIFY(readSignal.count() > 0);
}

void GetTestSuite::getIODevice()
{
    QTemporaryFile tempFile;
    Q_ASSERT(tempFile.open());
    QNetworkReply *reply = m_webdav.get(testDataPath, &tempFile);
    QSignalSpy errorSignal(reply, SIGNAL(error(QNetworkReply::NetworkError)));
    QSignalSpy readSignal(reply, SIGNAL(readyRead()));
    QSignalSpy finishedSignal(reply, SIGNAL(finished()));

    QVERIFY(finishedSignal.wait(DEFAULT_WAIT_TIMEOUT));
    QCOMPARE(errorSignal.count(), 0);
    QVERIFY(readSignal.count() > 0);
}

void GetTestSuite::getIODeviceWithRange()
{
    QTemporaryFile tempFile;
    Q_ASSERT(tempFile.open());
    QNetworkReply *reply = m_webdav.get(testDataPath, &tempFile, 10);
    QSignalSpy errorSignal(reply, SIGNAL(error(QNetworkReply::NetworkError)));
    QSignalSpy readSignal(reply, SIGNAL(readyRead()));
    QSignalSpy finishedSignal(reply, SIGNAL(finished()));

    QVERIFY(finishedSignal.wait(DEFAULT_WAIT_TIMEOUT));
    QCOMPARE(errorSignal.count(), 0);
    QVERIFY(readSignal.count() > 0);
}


