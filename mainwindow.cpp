#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MainWindow::setWindowTitle("New File");
    MainWindow::openapp();


    on_addTab_clicked();

    ui->tabWidget->setTabVisible(1,false);

    ui->tabWidget->widget(0)->setFocus();

    ui->tabWidget->tabBar()->setVisible(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}


QString filepath("-");

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


            pathfile[noba] = filepath;

        }

    }

    MainWindow::on_spinBox_valueChanged(ui->spinBox->value());
    MainWindow::setWindowTitle(filepath);

    on_tabWidget_currentChanged(noba);


    QString tabiz;
    QString nono(QChar('/'));
    for(int i = filepath.length() - 1; i >= 0; i--){
        if(filepath[i] != nono){
            tabiz.append(filepath[i]);
        }else {
            break;
        }

    }

    QString tabname;
    for(int i = tabiz.length() - 1; i >= 0; i--){
        tabname.append(tabiz[i]);
    }

    ui->tabWidget->setTabText(noba,tabname);
}

void MainWindow::on_SaveButton_clicked()
{

    if (filepath != "-"){
        QFile savefile(filepath);

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
                ui->working_file->setText(filepath);

                pathfile[noba] = filepath;

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

    QPlainTextEdit* go = new QPlainTextEdit;

    int bdfs = (QPTElist.length() - 1) - noba;
    go->clear();
    QPTElist[bdfs]->clear();

    pathfile[noba] = "-";

    ui->working_file->setText("-");


    MainWindow::on_spinBox_valueChanged(ui->spinBox->value());
    MainWindow::setWindowTitle("New File");

    QString nvsa = QString("Untitled %1").arg(xx + 1);
    xx = xx + 1;

    ui->tabWidget->setTabText(noba,nvsa);

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

        QJsonObject val = ref.toObject();


        val.insert("FontSize", siz);

        ref=val;

        jdoc.setObject(robj);

        file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
        file.write(jdoc.toJson());
        file.close();
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

    filepath = pathfile[index];
    ui->working_file->setText(filepath);

    if(pathfile[index] != "-"){
        MainWindow::setWindowTitle(pathfile[index]);
    }else{
        MainWindow::setWindowTitle("New File");
    }


}



void MainWindow::on_addTab_clicked()
{

    QString nvsa = QString("Untitled %1").arg(xx + 1);
    xx = xx + 1;

    QPlainTextEdit* go = new QPlainTextEdit;


    ui->tabWidget->insertTab(0,go,nvsa);

    QPTElist.append(go);

    filepath = "-";

    if (pathfile.length() == 0){
        pathfile.append(filepath);
    }else {
        pathfile.insert(0,filepath);
    }


    MainWindow::on_spinBox_valueChanged(ui->spinBox->value());

    ui->tabWidget->tabBar()->setVisible(true);

}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    if (pathfile.length() > 1){
        ui->tabWidget->removeTab(index);

        QPTElist.removeAt(QPTElist.length() - index - 1);

        pathfile.removeAt(index);

        on_tabWidget_currentChanged(noba);
    }

}


void MainWindow::on_actionOpen_In_New_Tab_triggered()
{

    QFileDialog open(this);

    open.setFileMode(QFileDialog::ExistingFile);

    open.setNameFilter("Any files (*)");

    open.setViewMode(QFileDialog::List);

    QStringList openfile;

    QString nvsa = QString("Untitled %1").arg(xx + 1);
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

            if (pathfile.length() == 0){

                pathfile.append(filepath);

            }else {

                pathfile.insert(0,filepath);

            }

        }

    }

    MainWindow::on_spinBox_valueChanged(ui->spinBox->value());
    MainWindow::setWindowTitle(filepath);
    ui->tabWidget->tabBar()->setVisible(true);



    QString tabiz;
    QString nono(QChar('/'));
    for(int i = filepath.length() - 1; i >= 0; i--){
        if(filepath[i] != nono){
            tabiz.append(filepath[i]);
        }else {
            break;
        }

    }

    QString tabname;
    for(int i = tabiz.length() - 1; i >= 0; i--){
        tabname.append(tabiz[i]);
    }

    ui->tabWidget->setTabText(noba,tabname);
}

