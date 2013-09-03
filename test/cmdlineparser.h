#ifndef CMDLINEPARSER_H
#define CMDLINEPARSER_H

#include <QtCore/QStringList>

/**
 * @brief The CmdLineParser class
 * Idea shamelessly ripped from https://github.com/flavio/qjson/blob/master/tests/cmdline_tester/
 *
 * This class in NOT thread safe
 */
class CmdLineParser
{
public:
    enum Result {Ok, Help, Error};

    CmdLineParser(const QStringList &arguments);
    Result parse();

    QString hostname() const;
    QString root() const;
    QString username() const;
    QString password() const;
    int port() const;
    bool quiet() const;
    QStringList skippedArguments() const;

    void showMessage(const QString &msg, bool error);

private:
    bool hasMoreArgs() const;
    const QString &nextArg();

    QStringList m_arguments;
    QStringList m_unparsedArgs;
    int m_pos;
    QString m_hostname;
    QString m_root;
    QString m_username;
    QString m_password;
    int m_port;
    bool m_quiet;
    static const QString m_helpMessage;
    QString m_error;
};

#endif // CMDLINEPARSER_H
