#include "aboutus.h"
#include "ui_aboutus.h"

Aboutus::Aboutus(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Aboutus)
{
    ui->setupUi(this);
    this->setWindowTitle("About us");
}

Aboutus::~Aboutus()
{
    delete ui;
}
