#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QRegularExpression>

QT_BEGIN_NAMESPACE
class QTextDocument;
QT_END_NAMESPACE

//! [0]
class myHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    myHighlighter(QTextDocument *parent = 0);
protected:
    void highlightBlock(const QString &text) override;

private:

    struct HighlightingRule
    {
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;


    QTextCharFormat open_close_tag_Format;
    QTextCharFormat commentTag_Format;
    QTextCharFormat tag_Format;
    QTextCharFormat  attributeValue_Format;
    QTextCharFormat  attribute_Format;
    QTextCharFormat equal_Format;
    QTextCharFormat data;

};


#endif // HIGHLIGHTER_H
