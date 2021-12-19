#include "fixdialog.h"
#include "ui_fixdialog.h"
#include "myhighlighter.h"
#include "XML_File.h"

#include<QFile>
#include <stdexcept>
#include<iostream>
#include<QMessageBox>
using namespace std;

QString curr_text;
QTextCharFormat fmt;
QString applyString ="No String";

bool change =false;

fixDialog::fixDialog(QWidget *parent,QString MYCurentText,int MYnumberOfLines, int * MYarray,QString myFileName,QString errorTags,bool modeState) :
    QDialog(parent),
    ui(new Ui::fixDialog)
{
    ui->setupUi(this);

     highlighter = new myHighlighter(ui->plainTextEdit->document());
    if(MYCurentText == " ")
    {
         throw std::invalid_argument( "empty Plain text");
    }

    if(modeState == true)
    {
        ui->plainTextEdit->setPalette(QPalette( Qt::black));
        ui->plainTextEdit_2->setPalette(QPalette( Qt::black));
    }

    this->myErrorTags = errorTags;
    this->myFixFileName = myFileName;
    this->showLines(MYCurentText);
    this->CurentText =  MYCurentText;
    this->numberOfLines = MYnumberOfLines;

   this->underLineMistakes( MYarray ,this->numberOfLines);


}

fixDialog::~fixDialog()
{
    delete ui;
}



void fixDialog::underLineMistakes(int arr[], int numberOfLines)
{

     ui->plainTextEdit->moveCursor(QTextCursor::Start);
    int j = 0;
    for(int i =1; i<=numberOfLines;i++)
    {
        if(arr[j] == i)
        {
            textUnderline();

            //errorLines(arr[j]);
             j++;

        }
        else
        {
            ui->plainTextEdit->moveCursor(QTextCursor::Down);
        }

    }

    errorLines(this->myErrorTags);

}


 void fixDialog::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
 {
     QTextCursor cursor = ui->plainTextEdit->textCursor();
     cursor.select(QTextCursor::LineUnderCursor);
     cursor.mergeCharFormat(format);
     ui->plainTextEdit->mergeCurrentCharFormat(format);
 }



 void fixDialog::textUnderline()
 {
     fmt.setUnderlineStyle(QTextCharFormat::SpellCheckUnderline);
     fmt.setUnderlineColor(Qt::red);
     fmt.setFontUnderline(true);
     mergeFormatOnWordOrSelection(fmt);
     ui->plainTextEdit->moveCursor(QTextCursor::Down);
     fmt.setUnderlineStyle(QTextCharFormat::NoUnderline);
     fmt.setFontUnderline(false);

 }

 void fixDialog::errorLines(QString text)
 {

      ui->plainTextEdit_2->setPlainText(text);

 }

 void fixDialog::showLines(QString Text)
 {


     //cout<<endl<<endl<<Text<<endl;
     QStringList myList;
     myList = Text.split("\n");
     for(int i =0; i<myList.size();i++)
     {
         QString sn = QString::number(i+1);
         ui->plainTextEdit->appendPlainText(sn+". "+myList[i]);
     }
 }


void fixDialog::on_button_Close_clicked()
{

fixDialog::close();
}




void fixDialog::on_button_ShowFix_clicked()
{


   string my_covertedFileName =  this->myFixFileName.toStdString();
   XML_File myNewFile(my_covertedFileName);
   string showedString = myNewFile.correctedFile();
   cout<<endl<<endl<<showedString<<endl;
   QString showedString_Q;
   showedString_Q = showedString_Q.fromStdString(showedString);
   applyString =  showedString_Q;

    ui->plainTextEdit->clear();
   showLines(showedString_Q);

}


void fixDialog::on_button_Apply_clicked()
{


    QMessageBox::StandardButton user_reply = QMessageBox::question(this,"Apply fix","By pressing on ok you will apply "
                                                                                    "this fix and modify your current file "
                                                                                    "are you sure you want to apply the fix?"
                                                     ,QMessageBox::Close| QMessageBox::Apply);
      if(user_reply == QMessageBox::Apply)
      {
          change = true;
          QFile file(this->myFixFileName);
          if(!file.open(QFile::WriteOnly|QFile::Text))
          {
              if(this->myFixFileName == " ")
              {
                  return;

              }

          }

           QTextStream out (&file);

           out<< applyString;
           file.flush();
           file.close();
           QMessageBox::information(this,"Fix error","Fix applied Successfuly");
           fixDialog::close();

      }
      else
      {

      }


}

QString fixDialog:: getApplyString()
{
    if(!change)
    {
        return this->CurentText;
    }
    return applyString;
}

