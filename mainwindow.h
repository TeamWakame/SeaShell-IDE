#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QFileSystemModel>

#include "highlighter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static void getSettings();

private slots:
    void on_filesView_doubleClicked(const QModelIndex &index);
    void on_actionFiles_views_toggled(bool arg1);

    void on_actionOpen_folder_triggered();

    void on_actionOpen_file_triggered();

    void on_actionAbout_Qt_triggered();

private:
    Ui::MainWindow *ui;
    void actu();
    MyHighlighter *highlighter;
    QFileSystemModel *model;
    QSettings *settings;
    QString endFile;
    bool isFileOpen;
};
#endif // MAINWINDOW_H
