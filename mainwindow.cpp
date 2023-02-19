#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MainWindow::setWindowTitle("New File");

    MainWindow::openapp();


    on_pushButton_clicked();

    ui->tabWidget->setTabVisible(1,false);

    ui->tabWidget->widget(0)->setFocus();

    ui->tabWidget->tabBar()->setVisible(false);

}

MainWindow::~MainWindow()
{

    delete ui;
}


QString filepath("-");
QString filepath1("-");

int xx = 0;
int noba;
int fontsize;

QList<QString> pathfile;
QList<QPlainTextEdit*> QPTElist;


void MainWindow::on_OpenButton_clicked()
{


    QFileDialog open(this);

    open.setFileMode(QFileDialog::ExistingFile);

    open.setNameFilter("Any files (*)");

    open.setViewMode(QFileDialog::List);

    QStringList openfile;

    if(open.exec())
    {
        openfile = open.selectedFiles();

        QFile data(openfile[0]);

        if(data.open(QFile::ReadOnly) | QFile::Truncate)
        {

            QTextStream soy(&data);

            QPTElist[QPTElist.length() - noba - 1]->clear();
            QPTElist[QPTElist.length() - noba - 1]->insertPlainText(soy.readAll());

            filepath = openfile[0];
            filepath1 = openfile[0];


            pathfile[noba] = filepath1;


            MainWindow::setWindowTitle(filepath1);

        }

    }

    MainWindow::on_spinBox_valueChanged(ui->spinBox->value());
    MainWindow::setWindowTitle(filepath);

    on_tabWidget_currentChanged(noba);

}

void MainWindow::openTab()
{

    QFileDialog open(this);

    open.setFileMode(QFileDialog::ExistingFile);

    open.setNameFilter("Any files (*)");

    open.setViewMode(QFileDialog::List);

    QStringList openfile;

    QString nvsa = QString("File %1").arg(xx + 1);
    xx = xx + 1;


    if(open.exec())
    {
        openfile = open.selectedFiles();

        QFile data(openfile[0]);

        if(data.open(QFile::ReadOnly) | QFile::Truncate)
        {
            QPlainTextEdit* go = new QPlainTextEdit;

            QTextStream soy(&data);

            QPTElist.append(go);

            go->clear();
            go->insertPlainText(soy.readAll());

            ui->tabWidget->insertTab(0,go,nvsa);

            filepath = openfile[0];
            filepath1 = openfile[0];

            if (pathfile.length() == 0){

                pathfile.append(filepath1);

            }else {

                pathfile.insert(0,filepath1);

            }

            MainWindow::setWindowTitle(filepath1);

        }

    }

    MainWindow::on_spinBox_valueChanged(ui->spinBox->value());
    MainWindow::setWindowTitle(filepath);
    ui->tabWidget->tabBar()->setVisible(true);

}

void MainWindow::on_SaveButton_clicked()
{

    if (filepath1 != "-"){
        QFile savefile(filepath1);

        if(savefile.open(QFile::WriteOnly) | QFile::Truncate)
        {
            int bdfs = (QPTElist.length() - 1) - noba;
            QTextStream boy(&savefile);
            boy << QPTElist[bdfs]->toPlainText();
        }
    }else
    {
        QFileDialog savel(this);
        savel.setFileMode(QFileDialog::AnyFile);

        savel.setAcceptMode(QFileDialog::AcceptSave);
        savel.setViewMode(QFileDialog::List);


        int bdfs = (QPTElist.length() - 1) - noba;

        QString fulltext(QPTElist[bdfs]->toPlainText());

        QStringList openfile;

        if(savel.exec())
        {

            openfile = savel.selectedFiles();

            QFile data(openfile[0]);

            if(data.open(QFile::ReadWrite) | QFile::Truncate)
            {
                filepath = openfile[0];
                filepath1 = openfile[0];
                ui->working_file->setText(filepath1);

                pathfile[noba] = filepath1;

                QTextStream roy(&data);
                roy << fulltext;
            }
        }
    }


    MainWindow::on_spinBox_valueChanged(ui->spinBox->value());
    MainWindow::setWindowTitle(filepath);
}


void MainWindow::on_SaveAsButton_clicked()
{
    QFileDialog saveas(this);
    saveas.setFileMode(QFileDialog::AnyFile);

    saveas.setAcceptMode(QFileDialog::AcceptSave);
    saveas.setViewMode(QFileDialog::List);
    saveas.setLabelText(QFileDialog::FileType,"fe");


    QStringList datsh;

    if(saveas.exec())
    {
        datsh = saveas.selectedFiles();

        QFile savefileas(datsh[0]);

        int bdfs = (QPTElist.length() - 1) - noba;
        QString fulltext(QPTElist[bdfs]->toPlainText());

        if(savefileas.open(QFile::ReadWrite) | QFile::Truncate)
        {
            QTextStream roy(&savefileas);
            roy << fulltext;

        }
    }

    MainWindow::on_spinBox_valueChanged(ui->spinBox->value());
    MainWindow::setWindowTitle(filepath);
}

void MainWindow::on_NewButton_clicked()
{
    filepath = "-";
    filepath1 = "-";

    QPlainTextEdit* go = new QPlainTextEdit;

    int bdfs = (QPTElist.length() - 1) - noba;
    go->clear();
    QPTElist[bdfs]->clear();

    pathfile[noba] = "";

    ui->working_file->setText("-");


    MainWindow::on_spinBox_valueChanged(ui->spinBox->value());
    MainWindow::setWindowTitle("New File");

}

void MainWindow::on_actionOpen_triggered()
{
    MainWindow::on_OpenButton_clicked();
}


void MainWindow::on_actionSave_triggered()
{
    MainWindow::on_SaveButton_clicked();
}


void MainWindow::on_actionSave_As_triggered()
{
    MainWindow::on_SaveAsButton_clicked();
}


void MainWindow::on_actionNew_File_triggered()
{
    MainWindow::on_NewButton_clicked();
}


void MainWindow::on_fontComboBox_currentFontChanged(const QFont &f)
{

    for(int i = 0; i < QPTElist.length(); i++){
        QPTElist[i]->setFont(f);
    }
    MainWindow::on_spinBox_valueChanged(ui->spinBox->value());

}


void MainWindow::on_spinBox_valueChanged(int arg1)
{

    fontsize = arg1;

    for(int i = 0; i < QPTElist.length(); i++){
        QFont f1 = QPTElist[i]->font();
        f1.setPointSize(arg1);
        QPTElist[i]->setFont(f1);

    }

    jsonadd(arg1);

}


// For CL
void MainWindow::opencl(QString clpath)
{
    QFile data(clpath);

    if(data.open(QFile::ReadOnly) | QFile::Truncate)
    {
        QTextStream soy(&data);

        filepath = clpath;
        ui->working_file->setText(filepath);


        QPTElist[QPTElist.length() - noba - 1]->clear();
        QPTElist[QPTElist.length() - noba - 1]->insertPlainText(soy.readAll());

        pathfile[noba] = filepath;

        MainWindow::setWindowTitle(filepath);
    }

    MainWindow::on_spinBox_valueChanged(ui->spinBox->value());
    MainWindow::setWindowTitle(filepath);

}

void MainWindow::getopencl(QString ron){

    if(ron != ""){

        opencl(ron);

    }

}


void MainWindow::on_NewWindow_clicked()
{
    MainWindow *b = new MainWindow;
    b->show();
}


void MainWindow::on_actionNew_Window_triggered()
{
    MainWindow::on_NewWindow_clicked();
}


void MainWindow::on_actionNew_Window_button_triggered()
{
    if(ui->NewWindow->isHidden() == false){
        ui->NewWindow->setHidden(true);
        ui->actionNew_Window_button->setText("New Window button");
    }else{
        ui->NewWindow->setHidden(false);
        ui->actionNew_Window_button->setText("New Window butttton   ✔");
    }

}

void MainWindow::jsonadd(int siz){

    QString path = QString("%1/.config/ced/config.json").arg(QDir::homePath());

    QFile file(path);


    if (QFileInfo::exists(file.fileName())){

        file.open(QIODevice::ReadOnly | QIODevice::Text);

        QJsonDocument jdoc = QJsonDocument::fromJson(file.readAll());

        file.close();


        QJsonObject robj = jdoc.object();
        QJsonValueRef ref = robj.find("Settings").value();

        QJsonObject mf = ref.toObject();

        QJsonObject val = ref.toObject();
        val.insert("FontSize", siz);


        ref=val;

        jdoc.setObject(robj);

        file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
        file.write(jdoc.toJson());
        file.close();
    }else{

        file.close();

        QFile file1("/etc/ced/config.json");

        file1.open(QIODevice::ReadOnly | QIODevice::Text);

        QJsonDocument jdoc1 = QJsonDocument::fromJson(file1.readAll());

        file1.close();


        QJsonObject robj1 = jdoc1.object();
        QJsonValueRef ref1 = robj1.find("Settings").value();

        QJsonObject mf1 = ref1.toObject();

        QJsonObject val1 = ref1.toObject();
        val1.insert("FontSize", siz);


        ref1=val1;

        jdoc1.setObject(robj1);

        file1.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
        file1.write(jdoc1.toJson());
        file1.close();
    }

}

void MainWindow::openapp()
{

    QString path = QString("%1/.config/ced/config.json").arg(QDir::homePath());

    QFile file(path);

    if (QFileInfo::exists(file.fileName())){

        file.open(QIODevice::ReadOnly | QIODevice::Text);

        QJsonDocument jdoc = QJsonDocument::fromJson(file.readAll());

        file.close();

        QJsonObject robj = jdoc.object();
        QJsonValueRef ref = robj.find("Settings").value();

        QJsonObject mf = ref.toObject();

        ui->spinBox->setValue(mf["FontSize"].toDouble());


    }else{

        file.close();

        QFile file1("/etc/ced/config.json");

        file1.open(QIODevice::ReadOnly | QIODevice::Text);

        QJsonDocument jdoc1 = QJsonDocument::fromJson(file1.readAll());

        file1.close();

        QJsonObject robj1 = jdoc1.object();
        QJsonValueRef ref1 = robj1.find("Settings").value();

        QJsonObject mf1 = ref1.toObject();

        ui->spinBox->setValue(mf1["FontSize"].toDouble());
    }


}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    noba = index;

    filepath1 = pathfile[index];
    ui->working_file->setText(filepath1);

    qDebug() << pathfile;
    qDebug() << pathfile.back();

}



void MainWindow::on_pushButton_clicked()
{

    QString nvsa = QString("file%1").arg(xx + 1);
    xx = xx + 1;

    QPlainTextEdit* go = new QPlainTextEdit;


    ui->tabWidget->insertTab(0,go,nvsa);

    ui->working_file->setText(filepath1);

    QPTElist.append(go);

    filepath1 = "-";

    if (pathfile.length() == 0){
        pathfile.append(filepath1);
    }else {
        pathfile.insert(0,filepath1);
    }



    ui->working_file->setText(filepath);
    MainWindow::setWindowTitle(filepath);


    MainWindow::on_spinBox_valueChanged(ui->spinBox->value());
    MainWindow::setWindowTitle("New File");

    ui->tabWidget->tabBar()->setVisible(true);

}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    if (pathfile.length() > 1){
        ui->tabWidget->removeTab(index);

        QPTElist.remove(QPTElist.length() - index - 1);

        pathfile.remove(index);
    }

}

