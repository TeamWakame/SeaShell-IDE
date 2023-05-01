#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QFileSystemModel>
#include <QList>

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

    void on_openedFilesView_clicked(const QModelIndex &index);

    void on_actionSave_file_as_triggered();

    void on_actionNew_file_triggered();

    void on_actionSave_file_triggered();

    void on_codeEditor_textChanged();

private:
    Ui::MainWindow *ui;
    void actu();
    void openedFile(QString filePath, QString message);
    void openFile(QString filePath);
    void saveFile(QString filePath, QString content);
    MyHighlighter *highlighter;
    QFileSystemModel *model;
    QSettings *settings;
    QString endFolder;
    QList<QString> openedFiles;
    QList<QString> openedFilesName;
    QString currentFilePath;
    QString currentTitle;
};
#endif // MAINWINDOW_H
