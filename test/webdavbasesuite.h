#ifndef WEBDAVBASESUITE_H
#define WEBDAVBASESUITE_H

#include <QObject>

class WebDAVBaseSuite : public QObject
{
    Q_OBJECT
public:
    virtual ~WebDAVBaseSuite() { }
    
signals:
    
public slots:

protected:
    explicit WebDAVBaseSuite(QString host, QString root, QString username, QString password ,
        int port, QObject *parent = 0);

    QString m_hostname;
    QString m_root;
    QString m_username;
    QString m_password;
    int m_port;

};

#endif // WEBDAVBASESUITE_H
