#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<myhighlighter.h>
#include<string>
#include<iostream>


using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void titleChange(void);
    ~MainWindow();


protected:
     void closeEvent(QCloseEvent *event) override;

     void static bubbleSort(int *arr, int n);

private slots:


    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_actionClose_triggered();

    void on_actionHelp_triggered();

    void on_pushButton_8_clicked();

    void on_actionAbout_us_triggered();

    void on_actionmaximize_triggered();

    void on_actionminimize_triggered();

    void on_actionNormal_size_triggered();

    void on_actionImport_XML_File_triggered();

    void on_actionClear_all_triggered();

    void on_actionSave_as_triggered();

    void on_button_convertToJSON_clicked();

    void on_button_Close_clicked();

    void on_button_help_clicked();

    void on_button_clearAll_clicked();

    void on_actionSave_triggered();

    void on_actionFont_triggered();

    void on_actionfont_triggered();

    void on_actionMode_switch_triggered();

    void on_actionRedo_triggered();

    void on_actionUndo_triggered();

    void on_actionConvert_to_JSON_triggered();


    void on_actionFormat_triggered();



    void on_actionCheck_for_errors_triggered();

    void on_actionZoom_in_triggered();

    void on_actionZoom_out_triggered();

    void on_actionZoom_to_default_triggered();

    void on_button_format_clicked();

    void on_button_Compress_clicked();

    //void on_pushButton_2_clicked();

    void on_actionDeCompress_triggered();

    void on_actionCompress_triggered();

    void on_actionPaste_triggered();

    void on_actionCop_triggered();

    void on_actionCut_triggered();

    void on_actionRestor_XML_triggered();

    void on_checkForErrors_clicked();

    void on_actionMinify_triggered();

    void on_actionView_Graph_triggered();

    void on_actionAnlayise_Graph_triggered();

private:
    Ui::MainWindow *ui;
    myHighlighter *highlighter;
    string my_window_file_name = " ";


    void static help();
   static string WriteGraphScript(vector<string> &vect1,vector<vector<string>>&vect2);



};
#endif // MAINWINDOW_H
