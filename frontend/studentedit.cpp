#include "myurl.h"
#include "studentedit.h"
#include "ui_studentedit.h"

StudentEdit::StudentEdit(QByteArray wt, QString fn, QString ln, QString id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentEdit)
{
    ui->setupUi(this);
    webToken=wt;
    ui->leFname->setText(fn);
    ui->leLname->setText(ln);
    id_student=id;
}

StudentEdit::~StudentEdit()
{
    delete ui;
}
void StudentEdit::on_btnCancel_clicked()
{
    this->close();
}

void StudentEdit::on_btnSave_clicked()
{
    QJsonObject jsonObj;
    jsonObj.insert("fname",ui->leFname->text());
    jsonObj.insert("lname",ui->leLname->text());
    jsonObj.insert("password",ui->lePassword->text());

    QString site_url=MyUrl::getBaseUrl()+"/student/"+id_student;
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    //WEBTOKEN ALKU
    QByteArray myToken=webToken;
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU

    updateManager = new QNetworkAccessManager(this);
    connect(updateManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(updateStudentSlot(QNetworkReply*)));

    reply = updateManager->put(request, QJsonDocument(jsonObj).toJson());
}




void StudentEdit::updateStudentSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;
    reply->deleteLater();
    updateManager->deleteLater();
    this->close();
}


