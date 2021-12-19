/*
********************************** Included liberaries and header files ************************************************
********************************** ************************************ ************************************************
*/


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"myhighlighter.h"
#include"helpwindow.h"
#include"aboutus.h"
#include<fixdialog.h>



#include<QCloseEvent>
#include <QMessageBox>

#include<QFile>
#include<QFileDialog>
#include<QFileInfo>
#include<QTextStream>

#include<QFont>
#include<QFontDialog>

#include"XML_File.h"
#include"xmlcompress.h"

#include<string>
#include<string.h>
#include<iostream>
using namespace std;


/*
******************************************   Global variables *******************************************************
********************************** ************************************ ************************************************
*/

bool closeIsPressed = false;
bool XML_on = true;
bool modeState = false;

QString my_file_name = " ";
QString CurrentText ="";
string my_converted_file_name = " ";

 xmlCompress myNewFileToCompress;

long long zoomInRange =0;
long long zoomOutRange =0;


/*
****************************************** Main Window Functions *****************************************************
********************************** ************************************ **********************************************
*/


//****************************************** 1.Constructor and Destructor ********************************************

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if(XML_on)
    {
     highlighter = new myHighlighter(ui->plainTextEdit->document());
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}


/********************************** 2.Overriding the close event ************************************************

  Here we override the close event so that when Alt+F4 is pressed the user gets a message that requests
  confirmation of closing.
  Function inputs: pointer to object of type QCloseEvent
  Function outputs: void
*/
void MainWindow::closeEvent(QCloseEvent *event)
{
    if(closeIsPressed)
    {
        closeIsPressed = false;
       event->accept();
    }

    else
    {

    QMessageBox::StandardButton user_reply = QMessageBox::question(this,"Quit","Are you sure you want to quit?"
                                                     ,QMessageBox::Yes | QMessageBox::No);
      if(user_reply == QMessageBox::Yes)
       {
          QApplication::quit();
      }
      else
      {
          event->ignore();


      }
    }

}


/***************************************** 3.Title Change Function ************************************************

 Here we want to change the mainWindow title to the file path in case of opening a file or restore it back to the
 Program name in case of closing the file
 if file name is " ": No file is opened. Thus keep the Program name on mainWindow title.
 if file name is not " ": Set the mainWindow title to file path

 Function input:void
 Function output:void
*/

void MainWindow:: titleChange(void)
{
    if(my_file_name == " ")
    {
        this->setWindowTitle("XML TO JSON CONVERTER");
    }
   else
    {
        this->setWindowTitle(my_file_name);
    }

}




//Clear button
void MainWindow::on_pushButton_3_clicked()
{
    if(my_file_name != " ")
    {
        this->my_window_file_name = my_file_name.toStdString();

        myNewFileToCompress.setFileName(this->my_window_file_name);
        myNewFileToCompress.deCompressFile();
        QString messa ="The file was de compressed Successfully";
        QMessageBox::information(this,"Compressing file",messa);

    }
    else
    {
        return;
    }


}


void MainWindow::on_actionClose_triggered()
{
    QMessageBox::StandardButton user_reply = QMessageBox::question(this,"Quit","Are you sure you want to quit?"
                                                   ,QMessageBox::Yes | QMessageBox::No);
    if(user_reply == QMessageBox::Yes)
    {
        closeIsPressed = true;
        QApplication::quit();
    }
}


void MainWindow::on_actionHelp_triggered()
{
    HelpWindow window1;
    window1.setModal(true);
    window1.exec();
}



void MainWindow::on_actionAbout_us_triggered()
{
    Aboutus window2;
    window2.setModal(true);
    window2.exec();
}


void MainWindow::on_actionmaximize_triggered()
{
  QWidget::showMaximized();

}


void MainWindow::on_actionminimize_triggered()
{
     QWidget::showMinimized();
}


void MainWindow::on_actionNormal_size_triggered()
{
     QWidget::showNormal();

}


void MainWindow::on_actionImport_XML_File_triggered()
{
    QString myFilter = "All Files (*.*) ;; XML File (*.xml) ;; JSON File (*.json)";
    my_file_name = QFileDialog::getOpenFileName(this,"Import new xml","C://",myFilter);



    QFileInfo fi(my_file_name);
    QString ext = fi.suffix();
    // QMessageBox::StandardButton user_reply =  QMessageBox::information(this,"About us",ext);
    if(ext == "xml" || ext == "XML" || ext == "xml.huff" || ext =="huff" || ext == "json" || ext == "JSON")
    {
        QFile file(my_file_name);

        if(!file.open(QFile::ReadOnly|QFile::Text))
        {
            QMessageBox::warning(this,"warning","File is not open");

        }

        this->titleChange();
        QTextStream in (&file);
        QString myText = in.readAll();
        CurrentText = myText;

        this->titleChange();

        ui->plainTextEdit->setPlainText(myText);
        file.close();
    }

    else
    {

        if(my_file_name == "")
        {
            my_file_name = " ";
            return;
        }

        QMessageBox::critical(this,"Error","The entered file is not xml file");
    }

}


void MainWindow::on_actionClear_all_triggered()
{
    ui->plainTextEdit->clear();
    my_file_name = " ";
    CurrentText ="";
    my_window_file_name = " ";
    this->titleChange();
}

//*****************************************Save as button*****************************************************
void MainWindow::on_actionSave_as_triggered()
{
     QString myFilter = "XML File (*.xml) ;; JSON File (*.json)";
     QString save_as_file_name = QFileDialog::getSaveFileName(this,"Save as","C://",myFilter);

     QFile file(save_as_file_name);

     if(!file.open(QFile::WriteOnly|QFile::Text))
     {
         if(save_as_file_name == "")
         {
             return;
         }
         QMessageBox::warning(this,"warning","File is not open");
     }

      this->titleChange();

      QTextStream out (&file);
      QString myText = ui->plainTextEdit->toPlainText();
      out<< myText;
      file.flush();
      file.close();

 }


void MainWindow::on_actionSave_triggered()
{
    if(my_file_name == " ")
    {
        QString myFilter = "XML File (*.xml) ;; JSON File (*.json)";
        QString save_as_file_name = QFileDialog::getSaveFileName(this,"Save as","C://",myFilter);
        my_file_name = save_as_file_name;

        QFile file(save_as_file_name);
        if(!file.open(QFile::WriteOnly|QFile::Text))
        {
            if(save_as_file_name == "")
            {
                my_file_name = " ";
                return;
            }
            my_file_name = " ";

        }
        this->titleChange();

         QTextStream out (&file);
         QString myText = ui->plainTextEdit->toPlainText();
         out<< myText;
         file.flush();
         file.close();

    }


    QFile file(my_file_name);
    if(!file.open(QFile::WriteOnly|QFile::Text))
    {
           QMessageBox::warning(this,"warning","File is not open");
    }

     QTextStream out (&file);
     QString myText = ui->plainTextEdit->toPlainText();
     out<< myText;
     file.flush();
     file.close();

}




//*********************************************************************************************************************
//                                                  Buttons
//**********************************************************************************************************************

void MainWindow::on_button_convertToJSON_clicked()
{
    if(my_file_name != " ")
    {
        this->my_window_file_name= my_file_name.toStdString();
        XML_File myNewFile(this->my_window_file_name);
        QString newS;
        newS = newS.fromStdString(myNewFile.toJSON());
        ui->plainTextEdit->setPlainText(newS);

    }
    else
    {
        return;
    }


}


//********************************************Minify *******************************************************

void MainWindow::on_pushButton_clicked()
{
    if(this->my_window_file_name != " ")
    {
        XML_File myNewFile(this->my_window_file_name);
        string minifiedString = myNewFile.mini_file();
        QString ShowedString;
        ShowedString = ShowedString.fromStdString(minifiedString);
        this->ui->plainTextEdit->setPlainText(ShowedString);
    }
    else
    {
        return;
    }



}

//********************************************Close Button *******************************************************
void MainWindow::on_button_Close_clicked()
{
    QMessageBox::StandardButton user_reply = QMessageBox::question(this,"Quit","Are you sure you want to quit?"
                                                   ,QMessageBox::Yes | QMessageBox::No);
    if(user_reply == QMessageBox::Yes)
    {
         closeIsPressed = true;
        QApplication::quit();

    }

}


//********************************************Help Button *******************************************************
void MainWindow::on_button_help_clicked()
{
    HelpWindow window1;
    window1.setModal(true);
    window1.exec();
}


void MainWindow::on_button_clearAll_clicked()
{
    ui->plainTextEdit->clear();
    my_file_name = " ";
    my_window_file_name= " ";
    CurrentText ="";
    this->titleChange();
}

// ***************************************Import button pressed*******************************************************

void MainWindow::on_pushButton_8_clicked()
{
    QString myFilter = "All Files (*.*) ;; XML File (*.xml) ;; JSON File (*.json)";
    my_file_name = QFileDialog::getOpenFileName(this,"Import new xml","C://",myFilter);

    std::string myconverted_file_name = my_file_name.toStdString();

    QFileInfo fi(my_file_name);
    QString ext = fi.suffix();

   if(ext == "xml" || ext == "XML" || ext == "xml.huff" || ext =="huff" || ext == "json" || ext == "JSON")
    {
        QFile file(my_file_name);
        if(!file.open(QFile::ReadOnly|QFile::Text))
        {

            QMessageBox::warning(this,"warning","File is not open");
        }

        QTextStream in (&file);
        QString myText = in.readAll();
        CurrentText = myText;

        this->titleChange();
        ui->plainTextEdit->setPlainText(myText);
        file.close();
    }

    else
    {

        if(my_file_name == "")
        {
            return;
        }
        QMessageBox::critical(this,"Error","The entered file is not xml file");
    }

}

void MainWindow::on_button_Compress_clicked()
{
    try {
        if(my_file_name != " ")
        {
            this->my_window_file_name = my_file_name.toStdString();

            myNewFileToCompress.setFileName(this->my_window_file_name);
            myNewFileToCompress.CompressFile();
            QString messa1 = "The file was compressed Successfully \n ";
            QString messa2 = "The original file size is :" + QString::number(myNewFileToCompress.getOrigSize())+" Bytes \n";
            QString messa3 = "The compressed file size is:"+ QString::number(myNewFileToCompress.getCompSize())+ "Bytes \n";
            QString messa = messa1+messa2+messa3;
            QMessageBox::information(this,"Compressing file",messa);

        }
        else
        {
            return;
        }

    }
    catch (exception e)
    {

    }



}

void MainWindow::on_actionFont_triggered()
{

    bool ok_for_this_font;
    QFont myFont = QFontDialog::getFont(&ok_for_this_font,this);
    if(ok_for_this_font)
    {
        ui->plainTextEdit->setFont(myFont);
    }
    else
    {
        return;
    }
}


void MainWindow::on_actionfont_triggered()
{

    bool ok_for_this_font;
    QFont myFont = QFontDialog::getFont(&ok_for_this_font,this);
    if(ok_for_this_font)
    {
        ui->plainTextEdit->setFont(myFont);
    }
    else
    {
        return;
    }
}


void MainWindow::on_actionMode_switch_triggered()
{

    static bool normalMode = false;
    modeState = !normalMode;
    if(!normalMode)
    {

         ui->plainTextEdit->setPalette(QPalette( Qt::black));
         normalMode = true;
         ui->toolBar->setPalette(QPalette( Qt::black));

    }
    else
    {
         ui->plainTextEdit->setPalette(QPalette( Qt::white));
         normalMode = false;
         ui->toolBar->setPalette(QPalette( Qt::white));

    }

}


void MainWindow::on_actionRedo_triggered()
{
    ui->plainTextEdit->redo();
}


void MainWindow::on_actionUndo_triggered()
{
    ui->plainTextEdit->undo();
}



void MainWindow::on_actionConvert_to_JSON_triggered()
{
    if(my_file_name != " ")
    {
        this->my_window_file_name= my_file_name.toStdString();
        XML_File myNewFile(this->my_window_file_name);
        QString newS;
        newS = newS.fromStdString(myNewFile.toJSON());
        ui->plainTextEdit->setPlainText(newS);

    }
    else
    {
        return;
    }



}


void MainWindow::on_actionFormat_triggered()
{

    try{
    if(my_file_name != " ")
    {
        this->my_window_file_name= my_file_name.toStdString();

        XML_File myNewFile(this->my_window_file_name);
        QString newS;


        cout<<myNewFile.printAligned();
        newS = newS.fromStdString(myNewFile.printAligned());
        ui->plainTextEdit->setPlainText(newS);

    }
    else
    {
        return;
    }
    }

    catch (exception e) {
        QString x = "Can not format this XML file \n";
        QString y = "This might be because the XML file is not correct or contains attributes inside tags \n";
        QString z = "It is prefred to check for errors first";
        QMessageBox::warning(this,"Format",x+y+z);
    }
}

//int array1[6] = {1,2,4};

void MainWindow::on_actionCheck_for_errors_triggered()
{
    if(my_file_name != " ")
    {

    this->my_window_file_name= my_file_name.toStdString();
    XML_File myNewFile(this->my_window_file_name);

    int x = 0;
    int* array1 = myNewFile.ErrorLines(&x);

    ifstream fin ;
        fin.open(this->my_window_file_name);
        string line ;
        int count = 0;
        while(fin){

            if(fin.eof())
                break;

            getline(fin,line);

            count++;
        }

        QString myTemp;
        myTemp = myTemp.fromStdString(myNewFile.Error_String());

    MainWindow::bubbleSort(array1,x);
    fixDialog myFixdialog(nullptr,ui->plainTextEdit->toPlainText(),count-1,array1,my_file_name,myTemp,modeState);
    myFixdialog.setModal(true);
    myFixdialog.setFixedSize(myFixdialog.size());
    myFixdialog.exec();
    ui->plainTextEdit->setPlainText(myFixdialog.getApplyString());


    }
    else
    {
        return;
    }
}



void MainWindow::on_actionZoom_in_triggered()
{
    ui->plainTextEdit->zoomIn(1);
    zoomInRange++;
}


void MainWindow::on_actionZoom_out_triggered()
{

     ui->plainTextEdit->zoomOut(1);
     zoomOutRange++;
}




void MainWindow::on_actionZoom_to_default_triggered()
{

    if(zoomInRange>zoomOutRange)
    {
        ui->plainTextEdit->zoomOut(zoomInRange - zoomOutRange);

    }
    else if(zoomInRange<zoomOutRange)
    {
        ui->plainTextEdit->zoomIn(zoomOutRange - zoomInRange);
    }
    else
    {
        return;
    }
    zoomInRange =0;
    zoomOutRange =0;
}





void MainWindow::on_button_format_clicked()
{
    try{
    if(my_file_name != " ")
    {
        this->my_window_file_name= my_file_name.toStdString();
        cout<<"here"<<endl;
        XML_File myNewFile(this->my_window_file_name);
        QString newS;
        cout<<this->my_window_file_name<<endl;
        cout<<"here"<<endl;
        cout<<myNewFile.printAligned();
        newS = newS.fromStdString(myNewFile.printAligned());
        ui->plainTextEdit->setPlainText(newS);

    }
    else
    {
        return;
    }
    }

    catch (exception e) {
        QString x = "Can not format this XML file \n";
        QString y = "This might be because the XML file is not correct or contains attributes inside tags \n";
        QString z = "It is prefred to check for errors first";
        QMessageBox::warning(this,"Format",x+y+z);
    }
}








void MainWindow::on_actionCompress_triggered()
{
    if(my_file_name != " ")
    {
        this->my_window_file_name = my_file_name.toStdString();

        myNewFileToCompress.setFileName(this->my_window_file_name);
        myNewFileToCompress.CompressFile();
        QString messa1 = "The file was compressed Successfully \n ";
        QString messa2 = "The original file size is :" + QString::number(myNewFileToCompress.getOrigSize())+"\n";
        QString messa3 = "The compressed file size is:" + QString::number(myNewFileToCompress.getCompSize())+ "\n";
        QString messa = messa1+messa2+messa3;
        QMessageBox::information(this,"Compressing file",messa);

    }
    else
    {
        QMessageBox::warning(this,"DeCompress","There is no file to Compress");
        return;
    }
}


void MainWindow::on_actionDeCompress_triggered()
{
    if(my_file_name != " ")
    {
        this->my_window_file_name = my_file_name.toStdString();

        myNewFileToCompress.setFileName(this->my_window_file_name);
        myNewFileToCompress.deCompressFile();
        QString messa ="The file was de compressed Successfully";
        QMessageBox::information(this,"Compressing file",messa);

    }
    else
    {
        QMessageBox::warning(this,"DeCompress","There is no file to deCompress");
        return;
    }

}


void MainWindow::on_actionPaste_triggered()
{
    ui->plainTextEdit->paste();
}


void MainWindow::on_actionCop_triggered()
{
    ui->plainTextEdit->copy();
}


void MainWindow::on_actionCut_triggered()
{
    ui->plainTextEdit->cut();
}


void MainWindow::on_actionRestor_XML_triggered()
{
    ui->plainTextEdit->setPlainText(CurrentText);
}


void MainWindow::on_checkForErrors_clicked()
{
    if(my_file_name != " ")
    {

    this->my_window_file_name= my_file_name.toStdString();
    XML_File myNewFile(this->my_window_file_name);

    int x = 0;
    int* array1 = myNewFile.ErrorLines(&x);

    ifstream fin ;
        fin.open(this->my_window_file_name);
        string line ;
        int count = 0;
        while(fin){

            if(fin.eof())
                break;

            getline(fin,line);

            count++;
        }

        QString myTemp;
        myTemp = myTemp.fromStdString(myNewFile.Error_String());
        MainWindow::bubbleSort(array1,x);


    fixDialog myFixdialog(nullptr,ui->plainTextEdit->toPlainText(),count-1,array1,my_file_name,myTemp,modeState);
    myFixdialog.setModal(true);
    myFixdialog.setFixedSize(myFixdialog.size());
    myFixdialog.exec();
     ui->plainTextEdit->setPlainText(myFixdialog.getApplyString());


    }
    else
    {
        return;
    }

}


void MainWindow::on_actionMinify_triggered()
{
    if(this->my_window_file_name != " ")
    {
        XML_File myNewFile(this->my_window_file_name);
        string minifiedString = myNewFile.mini_file();
        QString ShowedString;
        ShowedString = ShowedString.fromStdString(minifiedString);
        this->ui->plainTextEdit->setPlainText(ShowedString);
    }
    else
    {
        return;
    }
}

void MainWindow::bubbleSort(int *arr, int n)
{
    bool flag = true;
    for(int i =0; i<n-1;i++)
    {
        for(int j =0; j<n-i-1;j++)
        {
            if(arr[j]>arr[j+1])
            {
                swap(arr[j],arr[j+1]);
                flag = false;
            }
        }
        if(flag == true)
            break;
    }
}
