#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include "highlighter.h"

#include <QWidget>

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget *parent = nullptr);
    ~SettingsWindow();

private slots:

    void on_changeColorPushButton_clicked();

    void on_setAsDefaultPushButton_clicked();

private:
    Ui::SettingsWindow *ui;
    MyHighlighter *highlighter;
    QString exampleText;

};

#endif // SETTINGSWINDOW_H
