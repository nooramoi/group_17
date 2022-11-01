#include "studentwindow.h"
#include "ui_studentwindow.h"

StudentWindow::StudentWindow(QString id_student, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentWindow)
{
    ui->setupUi(this);
    ui->labelIdstudent->setText(id_student);

}

StudentWindow::~StudentWindow()
{
    delete ui;
}
