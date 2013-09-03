#include "webdavbasesuite.h"

WebDAVBaseSuite::WebDAVBaseSuite(QString host, QString root, QString username, QString password, int port,
                                 QObject *parent)
    : QObject(parent)
{
    m_hostname = host;
    m_root = root;
    m_username = username;
    m_password = password;
    m_port = port;
}
