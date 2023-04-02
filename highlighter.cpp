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
        settings->setValue("invertedCommasColor", "#DC735C");
    }
}

void MyHighlighter::highlightBlock(const QString &text)
{
    /*
     * Pattern syntax :
     * A defined word => "\\bWORD\\b" or "\\b(WORD1 | WORD2 |...)\\b"
     * A integer => "\\d"
     * A word => "\\w+" or "\\w" (letter)
     * Text between beacon => "\BEACON[^\"]*\BEACON" (beteween [] -> excluded)
     */
    QTextCharFormat redFormat;
    redFormat.setForeground(Qt::red);
    QRegularExpression redExpression("\\brouge\\b");
    QRegularExpressionMatchIterator i = redExpression.globalMatch(text);
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        setFormat(match.capturedStart(), match.capturedLength(), redFormat);
    }

    QTextCharFormat blueFormat;
    blueFormat.setForeground(QColor(settings->value("invertedCommasColor").toString()));
    QRegularExpression blueExpression("\"[^\"]*\"");
    i = blueExpression.globalMatch(text);
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        setFormat(match.capturedStart(), match.capturedLength(), blueFormat);
    }
}
