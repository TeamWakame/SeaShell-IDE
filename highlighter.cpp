#include "highlighter.h"
#include "mainwindow.h"

#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QFile>
#include<QCoreApplication>

MyHighlighter::MyHighlighter(QTextDocument *parent) : QSyntaxHighlighter(parent)
{
    if(QFile::exists(QCoreApplication::applicationDirPath()+"settings.ini"))
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
    }
}

void MyHighlighter::highlightBlock(const QString &text)
{
    /*
     * Pattern syntax :
     * A defined word => "\\bWORD\\b" or "\\bWORD1|WORD2|...\\b"
     * A character => "CHARACTER" (#, /, ...)
     * A integer => "\\d"
     * A word => "\\w+" or "\\w" (letter)
     * Text between beacon => "\BEACON[^\"]*\BEACON" (beteween [] -> excluded)
     */

    apply(settings->value("invertedCommasColor").toString(), "\"[^\"]*\"", text);
    apply(settings->value("invertedCommasColor").toString(), "\\/*[^\"]*\\*/", text);
    apply(settings->value("typeAndBaseWordColor").toString(), "\\bint|float|boolean|chr|str|if|else\\b", text);
    apply(settings->value("annotationColor").toString(), "\\##[^\"]*\\w+|##", text);
    apply(settings->value("operatorColor").toString(), "\\|\\||&&|!|^^|==|<<|>>|>=|<=", text);
    apply(settings->value("braceAndParthesisColor").toString(), "{|}|\\(|\\)", text);
}

void MyHighlighter::apply(QString color, QString pattern, QString textToApply)
{
    QTextCharFormat colorFormat;
    colorFormat.setForeground(QColor(color));
    QRegularExpression expression(pattern);
    QRegularExpressionMatchIterator i = expression.globalMatch(textToApply);
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        setFormat(match.capturedStart(), match.capturedLength(), colorFormat);
    }
}
