#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QSettings>

class MyHighlighter : public QSyntaxHighlighter
{
public:
    //MyHighlighter(QTextDocument *parent = 0) : QSyntaxHighlighter(parent) {}
    MyHighlighter(QTextDocument *parent = 0);
    void highlightBlock(const QString &text);

protected:

private:
    QSettings *settings;
};

#endif // HIGHLIGHTER_H
