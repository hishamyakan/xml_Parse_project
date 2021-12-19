#include "myhighlighter.h"
#include<QRegularExpression>

myHighlighter::myHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{

    HighlightingRule rule;

  tag_Format.setForeground(Qt::red);
  rule.pattern = QRegularExpression(QStringLiteral("<[^\n]*>"));
  rule.pattern.setPatternOptions(QRegularExpression::InvertedGreedinessOption);
  rule.format =  tag_Format;
  highlightingRules.append(rule);



  open_close_tag_Format.setForeground(Qt::blue);
  open_close_tag_Format.setFontWeight(QFont::Bold);
   const QString keywordPatterns[] = {
       QStringLiteral(">"),QStringLiteral("<"),QStringLiteral("=")

   };

   for (const QString &pattern : keywordPatterns) {
       rule.pattern = QRegularExpression(pattern);
       rule.format = open_close_tag_Format;
       highlightingRules.append(rule);

   }


   attribute_Format.setForeground(Qt::cyan);
   rule.pattern = QRegularExpression(QStringLiteral("\\b\\s[^\n]*="));
   //rule.pattern.setPatternOptions(QRegularExpression::InvertedGreedinessOption);
   rule.format =  attribute_Format;
   highlightingRules.append(rule);


 attributeValue_Format.setForeground(Qt::darkYellow);
 rule.pattern = QRegularExpression(QStringLiteral("\"[^\n]*\""));
 rule.pattern.setPatternOptions(QRegularExpression::InvertedGreedinessOption);
 rule.format =  attributeValue_Format;
 highlightingRules.append(rule);



equal_Format.setForeground(Qt::blue);
rule.pattern = QRegularExpression(QStringLiteral("="));
rule.format = equal_Format;
highlightingRules.append(rule);


 commentTag_Format.setForeground(Qt::darkGreen);
rule.pattern = QRegularExpression(QStringLiteral("<![^\n]*>"));
rule.format = commentTag_Format;
highlightingRules.append(rule);


}

void myHighlighter::highlightBlock(const QString &text)
{
    for (const HighlightingRule &rule : qAsConst(highlightingRules)) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }


 }


