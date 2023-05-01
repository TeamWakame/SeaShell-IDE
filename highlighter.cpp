#include "highlighter.h"
#include "mainwindow.h"

#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QFile>
#include<QCoreApplication>

MyHighlighter::MyHighlighter(QTextDocument *parent) : QSyntaxHighlighter(parent)
{
    settings = new QSettings(QCoreApplication::applicationDirPath()+"/settings.ini", QSettings::IniFormat, this);
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

    //Define dans apply all syntactic colouring
    apply(settings->value("typeAndBaseWordColor").toString(), "\\bint|float|boolean|chr|str|if|else\\b", text);
    apply(settings->value("operatorColor").toString(), "\\|\\||&&|!|^^|==|<<|>>|>=|<=", text);
    apply(settings->value("braceAndParthesisColor").toString(), "{|}|\\(|\\)", text);
    apply(settings->value("invertedCommasColor").toString(), "\"[^\"]*\"", text);
    apply(settings->value("invertedCommasColor").toString(), "\\/*[^\"]*\\*/", text);
    apply(settings->value("annotationColor").toString(), "\\##[^\"]*\\w+|##", text);
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
