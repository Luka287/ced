#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFont f1 = ui->plainTextEdit->font();
    f1.setPointSize(12);
    ui->plainTextEdit->setFont(f1);

    MainWindow::setWindowTitle("New File");


}

MainWindow::~MainWindow()
{
    delete ui;
}

QString filepath("");
QString kosa;

//MainWindow::setWindowTitle(filepath);
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
            ui->plainTextEdit->clear();
            ui->plainTextEdit->insertPlainText(soy.readAll());
            filepath = openfile[0];
            ui->working_file->setText(filepath);
            MainWindow::setWindowTitle(filepath);
        }

    }
    MainWindow::on_spinBox_valueChanged(ui->spinBox->value());
    MainWindow::setWindowTitle(filepath);
}


void MainWindow::on_SaveButton_clicked()
{
    if (filepath != ""){
        QFile savefile(filepath);

        QString kol(ui->plainTextEdit->toPlainText());

        if(savefile.open(QFile::WriteOnly) | QFile::Truncate)
        {
            QTextStream boy(&savefile);
            boy << kol;
        }
    }else
    {
        QFileDialog savel(this);
        savel.setFileMode(QFileDialog::AnyFile);

        savel.setAcceptMode(QFileDialog::AcceptSave);
        savel.setViewMode(QFileDialog::List);

        QString fulltext(ui->plainTextEdit->toPlainText());

        QStringList openfile;

        if(savel.exec())
        {

            openfile = savel.selectedFiles();

            QFile data(openfile[0]);

            if(data.open(QFile::ReadWrite) | QFile::Truncate)
            {
                filepath = openfile[0];
                ui->working_file->setText(filepath);

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

        ui->working_file->setText(datsh[0]);

        QString fulltext(ui->plainTextEdit->toPlainText());

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
   ui->plainTextEdit->clear();
   filepath = "";
   ui->working_file->setText("");

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
    ui->plainTextEdit->setFont(f);
    MainWindow::on_spinBox_valueChanged(ui->spinBox->value());


}


void MainWindow::on_spinBox_valueChanged(int arg1)
{
    QFont f1 = ui->plainTextEdit->font();
    f1.setPointSize(arg1);
    ui->plainTextEdit->setFont(f1);
}


// For Cl
void MainWindow::opencl(QString clpath)
{
        QFile data(clpath);

        if(data.open(QFile::ReadOnly) | QFile::Truncate)
        {
            QTextStream soy(&data);
            ui->plainTextEdit->clear();
            ui->plainTextEdit->insertPlainText(soy.readAll());
            filepath = clpath;
            ui->working_file->setText(filepath);
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
        ui->actionNew_Window_button->setText("New Window button   ✔");
    }

}

