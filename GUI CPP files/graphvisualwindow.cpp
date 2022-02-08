#include "graphvisualwindow.h"
#include "ui_graphvisualwindow.h"
#include <QPixmap>
#include<QDir>
#include<iostream>
#include<string>
#include<QMessageBox>

#include"XML_File.h"
#include"socialgraph.h"
#include"network.h"


using namespace std;

GraphVisualWindow::GraphVisualWindow(QWidget *parent,QString image,QString fileName) :
    QDialog(parent),
    ui(new Ui::GraphVisualWindow)
{
    ui->setupUi(this);
    this->myFileName = fileName;



    QDir::setCurrent(image);
    system("dot -Tpng -O textFile.dot");
    QPixmap item(QPixmap(image+"/textFile.dot.png"));
    ui->label->setPixmap(item);



}

GraphVisualWindow::~GraphVisualWindow()
{
    delete ui;
}

void GraphVisualWindow::on_pushButton_clicked()
{
GraphVisualWindow::close();
}


void GraphVisualWindow::on_Most_Inf_clicked()
{

    string s = this->myFileName.toStdString();
    XML_File myNewFile(s);

    SocialGraph myGraph = myNewFile.toGraph();
    vector<string> myVect = myGraph.mostInfluentialUser();
    QString toShow = "The most influencer user(s): \n";
    for(int i =0; i<(int)myVect.size();i++)
    {
        cout<<myVect[i];

         toShow += QString ::fromStdString(myVect[i]);
         toShow += "\n";

    }

    ui->textBrowser->setPlainText(toShow);
}


void GraphVisualWindow::on_Most_Act_clicked()
{
    string s = this->myFileName.toStdString();
    XML_File myNewFile(s);

    SocialGraph myGraph = myNewFile.toGraph();
    vector<string> myVect = myGraph.mostActiveUser();
    QString toShow = "The most active user(s): \n";
    for(int i =0; i<(int)myVect.size();i++)
    {
        cout<<myVect[i];

         toShow += QString ::fromStdString(myVect[i]);
         toShow += "\n";

    }

    ui->textBrowser->setPlainText(toShow);
}
bool GraphVisualWindow::checkInGraph(QString user1, vector<string> &vect1)
{
    bool check =false;

    if(vect1.size() == 0)
        return false;

    for(int i = 0; i<(int)vect1.size();i++)
    {

        if(user1.toLower() == QString::fromStdString( vect1[i]).toLower())

            return true;

    }
    return check;
}



void GraphVisualWindow::on_Mutual_clicked()
{
    try {
        string s = this->myFileName.toStdString();
        XML_File myNewFile(s);
        SocialGraph myGraph = myNewFile.toGraph();

        QString user1 = ui->User1->text();
        QString user2 = ui->User2->text();
        vector<string> vect1 = myGraph.UserNames();

        if(!GraphVisualWindow::checkInGraph(user1,vect1))
        {
             QMessageBox::warning(this,"warning","User 1 is not in the network \n Please check your input");
        }

        if(!GraphVisualWindow::checkInGraph(user2,vect1))
        {
             QMessageBox::warning(this,"warning","User 2 is not in the network \n Please check your input");
        }

        vector<string> myVect = myGraph.mutualFollowers(user1.toStdString(),user2.toStdString());

        QString toShow = "Mutal followers : \n";
        for(int i =0; i<(int)myVect.size();i++)
        {

             toShow += QString ::fromStdString(myVect[i]);
             cout<<myVect[i];
             toShow += "\n";

        }

        ui->textBrowser->setPlainText(toShow);

    }  catch (exception e) {
        ui->textBrowser->setPlainText("People you may know: No Suggestion to show\n");
    }

}


void GraphVisualWindow::on_People_You_clicked()
{
   try{
        string s = this->myFileName.toStdString();
        XML_File myNewFile(s);
        SocialGraph myGraph = myNewFile.toGraph();

        QString user = ui->User1->text();

        vector<string> vect1 = myGraph.UserNames();

        if((!GraphVisualWindow::checkInGraph(user,vect1)))
        {
             QMessageBox::warning(this,"warning","User 1 is not in the network \n Please check your input");
             throw exception();
        }


        //QMessageBox::warning(this,"warning","Here Before");
        vector<string> myVect = myGraph.Suggestions(user.toStdString());
         //QMessageBox::warning(this,"warning","HERE");

        QString toShow = "People You May Know : \n";

        if(myVect.size() == 0)

        {throw exception();}

            for(int i =0; i<(int)myVect.size();i++)
            {

                 toShow += QString ::fromStdString(myVect[i]);
                 toShow += "\n";

            }


            ui->textBrowser->setPlainText(toShow);

    }


    catch (exception e) {

        ui->textBrowser->setPlainText("People you may know: No Suggestion to show\n");

    }
}

