#include "mkdirtestsuite.h"

#include <qwebdav.h>
#include <qwebdavitem.h>
#include <qwebdavdirparser.h>

#include <QFile>
#include <QIODevice>
#include <QSignalSpy>

const int DEFAULT_WAIT_TIMEOUT = 5000;
const QString dir("/testdir/");
const QString expectedName("testdir");

MkdirTestSuite::MkdirTestSuite(QString host, QString root, QString username, QString password,
                               int port, QObject *parent)
    : WebDAVBaseSuite(host, root, username, password, port, parent)
{

}

void MkdirTestSuite::init()
{
    // Delete existing test directory first because it will fail our tests
    QNetworkReply *reply = m_webdav.remove(dir);
    QSignalSpy finishedSignal(reply, SIGNAL(finished()));
    QVERIFY(finishedSignal.wait(DEFAULT_WAIT_TIMEOUT));
    reply->deleteLater();
}

void MkdirTestSuite::mkdir()
{
    // Make directory
    m_webdav.setConnectionSettings(QWebdav::HTTP, m_hostname, m_root, m_username, m_password, m_port);
    {
        QNetworkReply *reply = m_webdav.mkdir(dir);
        QSignalSpy errorSignal(reply, SIGNAL(error(QNetworkReply::NetworkError)));
        QSignalSpy finishedSignal(reply, SIGNAL(finished()));
        QVERIFY(finishedSignal.wait(DEFAULT_WAIT_TIMEOUT));
        QCOMPARE(errorSignal.count(), 0);
        reply->deleteLater();
    }
    // Check created directory
    {
        QWebdavDirParser dirParser;
        QSignalSpy errorSignal(&dirParser, SIGNAL(errorChanged(QString)));
        QSignalSpy finishedSignal(&dirParser, SIGNAL(finished()));
        QVERIFY(dirParser.getDirectoryInfo(&m_webdav,dir));
        QVERIFY(finishedSignal.wait(DEFAULT_WAIT_TIMEOUT));
        QCOMPARE(errorSignal.count(), 0);
        QList<QWebdavItem> result = dirParser.getList();
        QVERIFY(result.size() == 1);
        QWebdavItem item = result.takeFirst();
        QVERIFY(item.isDir());
        QCOMPARE(item.name(), expectedName);
    }
}
