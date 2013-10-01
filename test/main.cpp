#include "cmdlineparser.h"
#include "testrunner.h"
#include "puttestsuite.h"
#include "removetestsuite.h"
#include "mkdirtestsuite.h"
#include "gettestsuite.h"

#include <QCoreApplication>
#include <QtTest>
#include <QTimer>
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
    TestRunner runner(cmdParser.skippedArguments(), &app);
    /**
      * Add tests here
      */
    runner.addTest(new PutTestSuite(cmdParser.hostname()
                                , cmdParser.root()
                                , cmdParser.username()
                                , cmdParser.password()
                                , cmdParser.port()
                                , &app
                                ));
    runner.addTest(new RemoveTestSuite(cmdParser.hostname()
                                   , cmdParser.root()
                                   , cmdParser.username()
                                   , cmdParser.password()
                                   , cmdParser.port()
                                   , &app
                                   ));
    runner.addTest(new MkdirTestSuite(cmdParser.hostname()
                                  , cmdParser.root()
                                  , cmdParser.username()
                                  , cmdParser.password()
                                  , cmdParser.port()
                                  , &app
                                  ));
    runner.addTest(new GetTestSuite(cmdParser.hostname()
                                  , cmdParser.root()
                                  , cmdParser.username()
                                  , cmdParser.password()
                                  , cmdParser.port()
                                  , &app
                                  ));
    QObject::connect(&runner, &TestRunner::finished, [&] (int result)
    {
        qDebug() << "Overall Result: " << (result == 0 ? "PASS" : "FAIL");
        app.quit();
    });
    QTimer::singleShot(0, &runner, SLOT(run()));

    return app.exec();
}

