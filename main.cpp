#include "mainwindow.h"

#include <QApplication>
#include <QCommandLineParser>
#include <QCoreApplication>
#include <QCommandLineOption>
#include <QDebug>
#include <QObject>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    a.setWindowIcon(QIcon("/usr/share/pixmaps/ced.png"));

    QApplication::setApplicationVersion("0.7.5");
    QCommandLineParser pars;

    pars.addHelpOption();
    pars.addVersionOption();

    QCommandLineOption openFile(QStringList() << "o" << "open-file",
                                QApplication::translate("main","Open the file"),
                                QApplication::translate("main","Path to file"));


    pars.addOption(openFile);

    pars.process(a);

    QString tarfile = pars.value(openFile);

    w.getopencl(tarfile);

    w.show();


    return a.exec();
}
