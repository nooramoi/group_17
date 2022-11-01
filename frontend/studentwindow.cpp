#include "studentwindow.h"
#include "qdebug.h"
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

const QString &StudentWindow::getWebToken() const
{
    return webToken;
}

void StudentWindow::setWebToken(const QString &newWebToken)
{
    webToken = newWebToken;
}

void StudentWindow::on_btnGrades_clicked()
{
    QString wb=this->getWebToken();
    qDebug()<<"webtoken="+wb;
}

