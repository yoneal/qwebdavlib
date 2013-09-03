#include "cmdlineparser.h"
#include "puttestsuite.h"
#include "removetestsuite.h"
#include "mkdirtestsuite.h"

#include <QCoreApplication>
#include <QtTest>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForCStrings(codec);
#endif

    // Parse arguments
    CmdLineParser cmdParser(app.arguments());
    CmdLineParser::Result cmdRes = cmdParser.parse();
    if (cmdRes == CmdLineParser::Error)
    {
        return -1;
    }

    // Perform tests
    PutTestSuite putTestSuite(cmdParser.hostname(), cmdParser.root(),
                              cmdParser.username(), cmdParser.password(), cmdParser.port(), &app);
    QTest::qExec(&putTestSuite, cmdParser.skippedArguments());
    RemoveTestSuite removeTestSuite(cmdParser.hostname(), cmdParser.root(),
                                    cmdParser.username(), cmdParser.password(), cmdParser.port(), &app);
    QTest::qExec(&removeTestSuite, cmdParser.skippedArguments());
    MkdirTestSuite mkdirTestSuite(cmdParser.hostname(), cmdParser.root(),
            cmdParser.username(), cmdParser.password(), cmdParser.port(), &app);
    QTest::qExec(&mkdirTestSuite, cmdParser.skippedArguments());

    qDebug() << "Done";

    return app.exec();
}
