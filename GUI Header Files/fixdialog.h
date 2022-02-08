#ifndef FIXDIALOG_H
#define FIXDIALOG_H

#include <QDialog>
#include<QTextCharFormat>
#include"myhighlighter.h"

namespace Ui {
class fixDialog;
}

class fixDialog : public QDialog
{
    Q_OBJECT

public:
    explicit fixDialog(QWidget *parent = nullptr,QString MYCurentText = " ",int MYnumberOfLines = 0, int * MYarray = nullptr,QString myFileName = " ",QString errorTags = " ",bool modeState = false);
    ~fixDialog();
    void mergeFormatOnWordOrSelection(const QTextCharFormat &format);

    void underLineMistakes(int arr[], int numberOfLines);

    void textUnderline();

    void errorLines(QString text);

    void setCurrentText(QString myCurentText);

    void setErrorLines(int arr[], int numberOfLines);

    void showLines(QString MYCurentText);

    QString getApplyString();



private slots:
    void on_button_Close_clicked();


    void on_button_ShowFix_clicked();

    void on_button_Apply_clicked();

private:
    Ui::fixDialog *ui;
    QString CurentText = " ";
    int numberOfLines;
     myHighlighter *highlighter;
     QString myErrorTags;
     QString myFixFileName;



};

#endif // FIXDIALOG_H
