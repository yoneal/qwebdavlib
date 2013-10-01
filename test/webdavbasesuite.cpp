#include "webdavbasesuite.h"

WebDAVBaseSuite::WebDAVBaseSuite(QString host, QString root, QString username, QString password, int port,
                                 QObject *parent)
    : QObject(parent)
    , m_webdav(parent)
{
    m_hostname = host;
    m_root = root;
    m_username = username;
    m_password = password;
    m_port = port;
}

void WebDAVBaseSuite::initTestCase()
{
    m_webdav.setConnectionSettings(QWebdav::HTTP
                                   , m_hostname
                                   , m_root
                                   , m_username
                                   , m_password
                                   , m_port);
}
