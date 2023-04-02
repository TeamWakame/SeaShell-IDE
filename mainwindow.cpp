#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "highlighter.h"

#include <QFileSystemModel>
#include <QTimer>
#include <QFile>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFileSystemModel *model = new QFileSystemModel;
    model->setRootPath(QCoreApplication::applicationDirPath());
    ui->treeView->setModel(model);
    ui->treeView->setRootIndex(model->index(QCoreApplication::applicationDirPath()));

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::actu);timer->start(1000);

    highlighter = new MyHighlighter(ui->textEdit->document());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::actu()
{
    highlighter->highlightBlock(ui->textEdit->toPlainText());
}

