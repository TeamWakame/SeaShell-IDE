#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "highlighter.h"
#include "settingswindow.h"

#include <QFileSystemModel>
#include <QTimer>
#include <QFile>
#include <QFileDialog>
#include <iostream>
#include <fstream>
#include <QDesktopServices>
#include <QMessageBox>
#include <QListWidgetItem>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    currentTitle = "SeaShell-IDE";
    this->setWindowTitle(currentTitle);

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
        settings->setValue("assignmentAndConstantColor", "#F9B900");

        settings->setValue("fontFamily", "Consolas");
        settings->setValue("fontSize", 12);
    }

    ui->codeEditor->setFontFamily(settings->value("fontFamily").toString());
    ui->codeEditor->setFontPointSize(settings->value("fontSize").toInt());

    highlighter = new MyHighlighter(ui->codeEditor->document());

    endFolder = "C:/";
    currentFilePath = "";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::actu()
{
    highlighter->highlightBlock(ui->codeEditor->toPlainText());
}

void MainWindow::on_codeEditor_textChanged()
{
    this->setWindowTitle(currentTitle + "*");
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this, "About Qt");
}

void MainWindow::on_actionFiles_views_toggled(bool arg1)
{
    if(!arg1)
        ui->filesView->hide();
    else
        ui->filesView->show();
}

void MainWindow::openedFile(QString filePath, QString message)
{
    /*
     * This method handles :
     *  - The interface
     *  - The list of open documents
     *  - The current document
     *  When a file is opened.
    */

    ui->codeEditor->setEnabled(true);
    ui->statusbar->showMessage(message);
    currentFilePath = filePath;

    QFileInfo current(filePath);
    currentTitle += " - " + current.baseName();
    this->setWindowTitle(currentTitle);

    if(!openedFiles.contains(filePath))
    {
        openedFiles.append(filePath);
        openedFilesName.append(current.baseName());
        ui->openedFilesView->addItem(filePath);
    }
}

void MainWindow::openFile(QString filePath)
{
    /*
     * This method open files and set content in the QTextEdit 'codeEditor'
    */

    ifstream file(filePath.toStdString().c_str());
    string text = "";
    if(file && filePath != "")
    {
        string line;

        while(getline(file, line)) // Pour récupérer tout le fichier
        {
            text += line + "\n";
        }
        ui->codeEditor->setPlainText(QString::fromStdString(text));

        openedFile(filePath, "Current file : " + filePath);
    }
    else
        QMessageBox::critical(this, "Opening error", "The opening of your file has failed.");
}

void MainWindow::saveFile(QString filePath, QString content)
{
    /*
     * This method save files with content
    */
    ofstream file(filePath.toStdString().c_str());

    if(file && filePath != "")
    {
        file << content.toStdString();
        this->setWindowTitle(currentTitle);
    }
    else
    {
        QMessageBox::critical(this, "Saving error", "Saving your file failed !\nFile : " + currentFilePath);
    }
}

void MainWindow::on_filesView_doubleClicked(const QModelIndex &index)
{
    QFileInfo  fi(model->filePath(index));
    if(fi.suffix() == "wk")
    {
        openFile(model->filePath(index));
    }
    else
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile(model->filePath(index))); //Open the selected file
    }
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

    endFolder = pathToFolder;
}


void MainWindow::on_actionOpen_file_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Ouvrir", endFolder, "Wakame file (*.wk)");

    openFile(fileName);
}

void MainWindow::on_openedFilesView_clicked(const QModelIndex &index)
{
    openFile(model->fileName(index));
}

void MainWindow::on_actionNew_file_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "New file", endFolder, "Wakame file (*.wk)");
    saveFile(fileName, "");
    openedFile(fileName, "Current file : " + fileName);
}

void MainWindow::on_actionSave_file_as_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as", endFolder, "Wakame file (*.wk)");
    saveFile(fileName, ui->codeEditor->toPlainText());
    openedFile(fileName, "Current file : " + fileName);
}


void MainWindow::on_actionSave_file_triggered()
{
    if (currentFilePath != "")
    {
        saveFile(currentFilePath, ui->codeEditor->toPlainText());
    }
    else
    {
        MainWindow::on_actionSave_file_as_triggered();
    }
}

void MainWindow::on_actionSettings_triggered()
{
    SettingsWindow *sWindow = new SettingsWindow();
    sWindow->show();
}

