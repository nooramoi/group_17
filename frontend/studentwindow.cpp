#include "studentwindow.h"
#include "qdebug.h"
#include "ui_studentwindow.h"
#include "myurl.h"

StudentWindow::StudentWindow(QString id_student, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentWindow)
{
    ui->setupUi(this);
    ui->labelIdstudent->setText(id_student);
    myStudentId=id_student;

}

StudentWindow::~StudentWindow()
{
    delete ui;
    delete objectStudentEdit;
    objectStudentEdit=nullptr;
}

void StudentWindow::setWebToken(const QByteArray &newWebToken)
{
    webToken = newWebToken;
}

void StudentWindow::on_btnGrades_clicked()
{

    QString site_url=MyUrl::getBaseUrl()+"/studentgrade/"+myStudentId;
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(webToken));
    //WEBTOKEN LOPPU
    gradeManager = new QNetworkAccessManager(this);

    connect(gradeManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(gradeSlot(QNetworkReply*)));

    reply = gradeManager->get(request);
}

void StudentWindow::gradeSlot(QNetworkReply *reply)
{
    //response_data=reply->readAll();
    //qDebug()<<response_data;
    QByteArray response_data=reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString grade="";
    foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        grade+=json_obj["name"].toString()+" , "+QString::number(json_obj["ects"].toInt())+" , "+
                QString::number(json_obj["grade"].toInt())+" , "+json_obj["grade_date"].toString()+"\r\n";
    }

    qDebug()<<grade;

    ui->textGrades->setText(grade);

    reply->deleteLater();
    gradeManager->deleteLater();
}


void StudentWindow::on_btnMyData_clicked()
{
    QString site_url=MyUrl::getBaseUrl()+"/student/"+myStudentId;
    QNetworkRequest request((site_url));
    //qDebug()<<site_url;
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(webToken));
    //WEBTOKEN LOPPU
    dataManager = new QNetworkAccessManager(this);

    connect(dataManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(dataSlot(QNetworkReply*)));

    reply = dataManager->get(request);
}



void StudentWindow::dataSlot(QNetworkReply *reply)
{
    //qDebug()<<reply->readAll();
    QByteArray response_data=reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();

    fname=json_obj["fname"].toString();
    lname=json_obj["lname"].toString();

    QString myData=myStudentId+"\r\n"+fname+"\r\n"+lname;

    ui->textData->setText(myData);
    ui->btnUpdate->setEnabled(true);
    reply->deleteLater();
    dataManager->deleteLater();
}

void StudentWindow::on_btnUpdate_clicked()
{
    objectStudentEdit=new StudentEdit(webToken,fname,lname,myStudentId);
    objectStudentEdit->show();

}

