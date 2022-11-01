#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnLogin_clicked()
{
    id_student=ui->textIdStudent->text();
    QString password=ui->textPassword->text();

    QJsonObject jsonObj;
    jsonObj.insert("id_student",id_student);
    jsonObj.insert("password",password);

    QString site_url=MyUrl::getBaseUrl()+"/login";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");


    loginManager = new QNetworkAccessManager(this);
    connect(loginManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(loginSlot(QNetworkReply*)));

    reply = loginManager->post(request, QJsonDocument(jsonObj).toJson());


}

void MainWindow::loginSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;
    int test=QString::compare(response_data,"false");
    qDebug()<<test;
    if(test==0){
        ui->textIdStudent->clear();
        ui->textPassword->clear();
        ui->labelInfo->setText("Tunnus ja salasana eivät täsmää");
    }
    else {
        objectStudentWindow=new StudentWindow(id_student);
        objectStudentWindow->setWebToken(response_data);
        objectStudentWindow->show();
    }
}

