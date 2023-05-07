#include "settingswindow.h"
#include "./ui_settingswindow.h"
#include "highlighter.h"

#include <QList>
#include <QColor>
#include <QColorDialog>
#include <QSettings>
#include <QFile>
#include <QMessageBox>

SettingsWindow::SettingsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Settings");

    ui->textPartComboBox->addItem("Inverted commas");
    ui->textPartComboBox->addItem("Types and bases words");
    ui->textPartComboBox->addItem("Annotations");
    ui->textPartComboBox->addItem("Operators");
    ui->textPartComboBox->addItem("Brace and parthesis");

    exampleText = "##Example text";
    ui->exampleCodeEditor->setPlainText(exampleText);

    highlighter = new MyHighlighter(ui->exampleCodeEditor->document());
    highlighter->highlightBlock(ui->exampleCodeEditor->toPlainText());
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}


void SettingsWindow::on_changeColorPushButton_clicked()
{
    QColorDialog colorSelector;
    QColor color = colorSelector.getColor(Qt::black, this, "Color selector - " + ui->textPartComboBox->currentText());

    QSettings settings(QCoreApplication::applicationDirPath()+"/settings.ini", QSettings::IniFormat, this);

    switch (ui->textPartComboBox->currentIndex())
    {
        case 0:
            settings.setValue("invertedCommasColor", color);
            break;
        case 1:
            settings.setValue("typeAndBaseWordColor", color);
            break;
        case 2:
            settings.setValue("annotationColor", color);
            break;
        case 3:
            settings.setValue("operatorColor", color);
            break;
        case 4:
            settings.setValue("braceAndParthesisColor", color);
            break;
        default:
            break;
    }

    ui->exampleCodeEditor->setPlainText(exampleText);
}


void SettingsWindow::on_setAsDefaultPushButton_clicked()
{
    if(QFile::remove(QCoreApplication::applicationDirPath()+"/settings.ini"))
        QMessageBox::information(this, "Success", "The syntax highlighting parameters have been set to their default values.\nYou must restart for the changes to take effect.");
    else
        QMessageBox::critical(this, "Error", "The syntax highlighting parameters have not been set to their default values.");
}

