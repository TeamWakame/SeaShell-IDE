#include "settingswindow.h"
#include "./ui_settingswindow.h"
#include "highlighter.h"

#include <QList>
#include <QColor>
#include <QColorDialog>
#include <QSettings>
#include <QFile>
#include <QMessageBox>
#include <QFont>
#include <QFontDialog>

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
    ui->textPartComboBox->addItem("Assignment and constant");

    exampleText = "##Example text##\n\n##Types (Types and bases words)\nint, float, boolean, chr, str\n\n##Conditions (Types and bases words)\nif, if else, else\n\n"
                  "##Operators (Operators)\n||, &&, !, ^^, ==, <<, >>, >=, <="
                  "\n\n##Declaration (Assignment and constant)\nNon-constant : <TYPE> <NAME> -> <VALUE>;\nConstant : <TYPE> c <NAME> -> <VALUE>;\nAffectation : <NAME> -> <VALUE>"
                  "\n\n##Braces && Parthesis (Brace and parthesis)\n(, ), {, }, [, ]\n\n##Annotations (Annotations && Inverted commas)\n"
                  "##For one line\n/*For multiple lines (doesn't work yet) (Inverted commas)*/\n\"For string (Inverted commas)\"";
    ui->exampleColorCodeEditor->setPlainText(exampleText);
    ui->exampleFontCodeEditor->setPlainText(exampleText);

    highlighter = new MyHighlighter(ui->exampleColorCodeEditor->document());
    highlighter->highlightBlock(ui->exampleColorCodeEditor->toPlainText());
    highlighter = new MyHighlighter(ui->exampleFontCodeEditor->document());
    highlighter->highlightBlock(ui->exampleFontCodeEditor->toPlainText());
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
        case 5:
            settings.setValue("assignmentAndConstantColor", color);
        default:
            break;
    }

    ui->exampleColorCodeEditor->setPlainText(exampleText);
}


void SettingsWindow::on_setAsDefaultColorPushButton_clicked()
{
    QSettings settings(QCoreApplication::applicationDirPath()+"/settings.ini", QSettings::IniFormat, this);

    settings.setValue("invertedCommasColor", "#153AE3");
    settings.setValue("typeAndBaseWordColor", "#D45A40");
    settings.setValue("annotationColor", "#6C87FF");
    settings.setValue("printColor", "#E8DE42");
    settings.setValue("operatorColor", "#A69C00");
    settings.setValue("braceAndParthesisColor", "#FF39E7");
    settings.setValue("assignmentAndConstantColor", "#F9B900");

    QMessageBox::information(this, "Set as default (color)", "Syntax highlighting parameters have been successfully reset to their default values.");
}


void SettingsWindow::on_setAsDefaultFontPushButton_clicked()
{
    QSettings settings(QCoreApplication::applicationDirPath()+"/settings.ini", QSettings::IniFormat, this);

    settings.setValue("fontFamily", "Consolas");
    settings.setValue("fontSize", 12);

    QMessageBox::information(this, "Set as default (font)", "The font parameters have been successfully reset to their default values. You'll need to reboot for the changes to take effect.");
}

void SettingsWindow::on_selectFontPushButton_clicked()
{
    QSettings settings(QCoreApplication::applicationDirPath()+"/settings.ini", QSettings::IniFormat, this);

    ui->exampleFontCodeEditor->selectAll();

    bool ok;
    QFontDialog fontDialog;
    QFont font = fontDialog.getFont(&ok, QFont("Consolas", 12), this, "Select font");
    ui->exampleFontCodeEditor->setCurrentFont(font);

    ui->selectFontComboBox->setCurrentFont(font);
    ui->selectFontSizeSpinBox->setValue(font.pointSize());

    QTextCursor cursor = ui->exampleFontCodeEditor->textCursor();
    cursor.clearSelection();
    ui->exampleFontCodeEditor->setTextCursor(cursor);

    settings.setValue("fontFamily", ui->selectFontComboBox->currentText());
    settings.setValue("fontSize", ui->selectFontSizeSpinBox->value());
    QMessageBox::information(this, "Cahnge font", "You'll need to reboot for the changes to take effect.");
}

