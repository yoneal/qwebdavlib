#include "qexample.h"

QExample::QExample(QObject *parent) :
    QObject(parent)
{
    w.setConnectionSettings(QWebdav::HTTPS, "192.168.17.125", "/root/", "prnsoft", "prnsoft", 443
                            , QCryptographicHash::Sha1, "a2:e1:8e:c5:65:64:0a:72:ff:56:dc:3c:51:46:8f:d7:d1:7f:3f:fb");
//    w.setConnectionSettings(QWebdav::HTTP, "192.168.17.111", "/root/", "prnsoft", "prnsoft", 80
//                            , "", "");
    connect(&p, SIGNAL(finished()), this, SLOT(printList()));
    connect(&p, SIGNAL(errorChanged(QString)), this, SLOT(printError(QString)));
    connect(&w, SIGNAL(connectionError(QString)), this, SLOT(printError(QString)));
    connect(&w, SIGNAL(sslCertificateError(QList<QSslError>)), this, SLOT(printError(QList<QSslError>)));
    m_path = "/";
}

void QExample::printList()
{
    QList<QWebdavItem> list = p.getList();

    QWebdavItem item;
    foreach(item, list) {
        qDebug() << item.name();

        QNetworkReply *reply = w.get(item.path());
        connect(reply, SIGNAL(readyRead()), this, SLOT(replySkipRead()));
        m_replyList.append(reply);
    }
}

void QExample::printError(QString errorMsg)
{
    qDebug() << "QWebdav::printErrors()  errorMsg == " << errorMsg;
}

void QExample::printError(QList<QSslError> errors)
{
    QSslError error;
    foreach (error, errors)
    {
        qDebug() << "QWebdav::printErrors()  errorMsg == " << error.errorString();
    }
}

void QExample::replySkipRead()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(QObject::sender());
    if (reply==0)
        return;

    QByteArray ba = reply->readAll();

    qDebug() << "QWebdav::replySkipRead()   skipped " << ba.size() << " reply->url() == " << reply->url().toString(QUrl::RemoveUserInfo);
}

void QExample::start()
{
    p.listDirectory(&w, m_path);
}
