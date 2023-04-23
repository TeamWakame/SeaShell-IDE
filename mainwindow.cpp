#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "highlighter.h"

#include <QFileSystemModel>
#include <QTimer>
#include <QFile>
#include <QFileDialog>
#include <iostream>
#include <fstream>
#include <QDesktopServices>
#include <QMessageBox>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("SeaShell-IDE");

    ui->actionFiles_views->setChecked(0);
    ui->filesView->hide();

    if(QFile::exists(QCoreApplication::applicationDirPath()+"/settings.ini"))
        settings = new QSettings(QCoreApplication::applicationDirPath()+"/settings.ini", QSettings::IniFormat, this);
    else
    {
        settings = new QSettings(QCoreApplication::applicationDirPath()+"/settings.ini", QSettings::IniFormat, this);
        settings->setValue("invertedCommasColor", "#153AE3");
        settings->setValue("typeAndBaseWordColor", "#D45A40");
        settings->setValue("annotationColor", "#6C87FF");
        settings->setValue("printColor", "#E8DE42");
        settings->setValue("operatorColor", "#A69C00");
        settings->setValue("braceAndParthesisColor", "#FF39E7");
        settings->setValue("fontFamily", "Consolas");
        settings->setValue("fontSize", 12);
    }

    ui->codeEditor->setFontFamily(settings->value("fontFamily").toString());
    ui->codeEditor->setFontPointSize(settings->value("fontSize").toInt());

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::actu);timer->start(1000);

    highlighter = new MyHighlighter(ui->codeEditor->document());

    endFile = "C:/";
    isFileOpen = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::actu()
{
    highlighter->highlightBlock(ui->codeEditor->toPlainText());
}


void MainWindow::on_filesView_doubleClicked(const QModelIndex &index)
{
    QFileInfo fi(model->filePath(index));
    ifstream file(model->filePath(index).toStdString().c_str());
    QString text = "";
    if(fi.suffix() == "wk" && file)
    {
        string line;

        while(getline(file, line)) // Pour récupérer tout le fichier
        {
            text += QString::fromStdString(line);
        }
        ui->codeEditor->setText(text);
    }
    else
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile(model->filePath(index))); //Open the selected file
    }
}

void MainWindow::on_actionFiles_views_toggled(bool arg1)
{
    if(!arg1)
        ui->filesView->hide();
    else
        ui->filesView->show();
}


void MainWindow::on_actionOpen_folder_triggered()
{
    QString pathToFolder = QFileDialog::getExistingDirectory(this, "Open folder", "C:");
    model = new QFileSystemModel;
    model->setRootPath(pathToFolder);
    ui->filesView->setModel(model);
    ui->filesView->setRootIndex(model->index(pathToFolder));

    ui->filesView->show();
    ui->actionFiles_views->setChecked(1);
}


void MainWindow::on_actionOpen_file_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Ouvrir", endFile, "Wakame file (*.wk)");

    string FileName = fileName.toStdString();
    ifstream strFileName(FileName.c_str());

    if (fileName != "")
    {
        if(strFileName)
        {
            string ligne;
            string texte;

            ui->codeEditor->clear();

            while(std::getline(strFileName, ligne)) // Pour récupérer tout le fichier
            {
                texte += ligne;
                // ui->textEdit->append(QString::fromStdString(ligne));
            }
            ui->codeEditor->setHtml(QString::fromStdString(texte));
        }
        else
        {
            QMessageBox::critical(this, "Erreur d'ouverture", "L'ouverture de votre fichier a échoué");
        }

        isFileOpen = true;
        endFile = fileName;

        ui->statusbar->showMessage("Current file : "+fileName);
    }
}


void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this, "About Qt");
}

