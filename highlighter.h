#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QSettings>

class MyHighlighter : public QSyntaxHighlighter
{
public:
    MyHighlighter(QTextDocument *parent = 0);
    void highlightBlock(const QString &text);

protected:

private:
    QSettings *settings;
    void apply(QString color, QString pattern, QString textToApply);
};

#endif // HIGHLIGHTER_H
