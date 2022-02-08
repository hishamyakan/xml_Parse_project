#ifndef GRAPHVISUALWINDOW_H
#define GRAPHVISUALWINDOW_H

#include <QDialog>
#include <iostream>
#include<string>

using namespace std;
namespace Ui {
class GraphVisualWindow;
}

class GraphVisualWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GraphVisualWindow(QWidget *parent = nullptr, QString image= " ",QString fileName =" ");
    ~GraphVisualWindow();

private slots:
    void on_pushButton_clicked();

    void on_Most_Inf_clicked();

    void on_Most_Act_clicked();

    void on_Mutual_clicked();

    void on_People_You_clicked();

private:
    Ui::GraphVisualWindow *ui;
    QString imagePath;
    QString myFileName;

    static bool checkInGraph(QString user1,vector<string> &vect1);
};

#endif // GRAPHVISUALWINDOW_H
