#include "mainwindow.h"

#include <QApplication>
#include <QCommandLineParser>
#include <QCoreApplication>
#include <QCommandLineOption>
#include <QDebug>
#include <QObject>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QApplication::setApplicationVersion("1.0");
    QCommandLineParser pars;

    pars.addHelpOption();
    pars.addVersionOption();


    QCommandLineOption openFile(QStringList() << "o" << "open-file",
    QApplication::translate("main","Open the file"),
    QApplication::translate("main","Files?"));


    pars.addOption(openFile);

    pars.process(a);

    QString tarfile = pars.value(openFile);

    w.getopencl(tarfile);

    w.show();

    return a.exec();
}
