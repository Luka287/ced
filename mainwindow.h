#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QFile>
#include <QDebug>
#include <QList>
#include <QFont>
#include <QStringLiteral>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QDir>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void opencl(QString clpath);
    void getopencl(QString ron);

private slots:

    void on_OpenButton_clicked();

    void on_SaveButton_clicked();

    void on_SaveAsButton_clicked();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_As_triggered();

    void on_NewButton_clicked();

    void on_fontComboBox_currentFontChanged(const QFont &f);

    void on_spinBox_valueChanged(int arg1);

    void on_actionNew_File_triggered();

    void on_NewWindow_clicked();

    void on_actionNew_Window_triggered();

    void on_actionNew_Window_button_triggered();

    void jsonadd(int siz);

    void openapp();

private:
   Ui::MainWindow *ui;

};


#endif // MAINWINDOW_H
