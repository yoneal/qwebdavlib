#include "cmdlineparser.h"

#include <QDebug>
#include <QStringBuilder>
#include <QFileInfo>
#include <QCoreApplication>

const QString CmdLineParser::m_helpMessage = QLatin1String(
        "Usage: tester [options] \n\n"
        "Run end-to-end tests on a WebDAV server\n"
        "--verbose              Be very noisy\n"
        "--help                 Displays this help.\n"
        "--hostname host        IP Address or host names are valid. Defaults to localhost\n"
        "--root root_url        URL to the root path. Defaults to '\'\n"
        "--port port_number     Defaults to 80.\n"
        "--username name        Defaults to none.\n"
        "--password password    Defaults to none.\n"
            );

CmdLineParser::CmdLineParser(const QStringList &arguments)
    : m_pos(0),
      m_quiet(true),
      m_hostname("localhost"),
      m_root("/"),
      m_port(80)
{
    for (int i = 1; i < arguments.count(); ++i) {
        const QString &arg = arguments.at(i);
        m_arguments.append(arg);
    }
}

CmdLineParser::Result CmdLineParser::parse()
{
    bool showHelp = false;

    while (m_error.isEmpty() && hasMoreArgs()) {
        const QString &arg = nextArg();

        if (arg.toLower() == QLatin1String("--hostname"))
        {
            if (!hasMoreArgs()) {
                m_error = QString(QLatin1String("Missing hostname argument"));
                continue;
            }
            m_hostname = nextArg();
        } else if (arg.toLower() == QLatin1String("--root"))
        {
            if (!hasMoreArgs()) {
                m_error = QString(QLatin1String("Missing root argument"));
                continue;
            }
            m_root = nextArg();
            //ToDo: add error checking for url
        } else if (arg.toLower() == QLatin1String("--username"))
        {
            if (!hasMoreArgs()) {
                m_error = QString(QLatin1String("Missing username argument"));
                continue;
            }
            m_username = nextArg();
        } else if (arg.toLower() == QLatin1String("--password"))
        {
            if (!hasMoreArgs()) {
                m_error = QString(QLatin1String("Missing password argument"));
                continue;
            }
            m_password = nextArg();
        } else if (arg.toLower() == QLatin1String("--port"))
        {
            if (!hasMoreArgs()) {
                m_error = QString(QLatin1String("Missing port argument"));
                continue;
            }
            m_port = nextArg().toInt();
        }
        else if (arg.toLower() == QLatin1String("--help"))
            showHelp = true;
        else if (arg.toLower() == QLatin1String("--verbose"))
            m_quiet = false;
        else {
//            m_error = QString(QLatin1String("Unknown option: %1")).arg(arg);
            m_unparsedArgs << arg;
        }
    }

    if (showHelp) {
        showMessage(m_helpMessage, false);
        return (!m_error.isEmpty()) ? Error: Help;
    }
    if (!m_error.isEmpty()) {
        showMessage(m_error + QLatin1String("\n\n\n") + m_helpMessage, true);
        return Error;
    }
    return Ok;
}

bool CmdLineParser::hasMoreArgs() const
{
    return m_pos < m_arguments.count();
}

const QString &CmdLineParser::nextArg()
{
    Q_ASSERT(hasMoreArgs());
    return m_arguments.at(m_pos++);
}

void CmdLineParser::showMessage(const QString &msg, bool error)
{
    QString message = QLatin1String("<pre>") % msg % QLatin1String("</pre>");
    if (error)
        qCritical() << QLatin1String("Error") << message;
    else
        qWarning() << QLatin1String("Notice") << message;
}

QString CmdLineParser::hostname() const
{
    return m_hostname;
}

QString CmdLineParser::root() const
{
    return m_root;
}

QString CmdLineParser::username() const
{
    return m_username;
}

QString CmdLineParser::password() const
{
    return m_password;
}

int CmdLineParser::port() const
{
    return m_port;
}

bool CmdLineParser::quiet() const
{
    return m_quiet;
}

QStringList CmdLineParser::skippedArguments() const
{
    return m_unparsedArgs;
}
