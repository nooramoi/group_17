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

    //qDebug()<<"webtoken="+wb;
    QString site_url=MyUrl::getBaseUrl()+"/studentgrade/"+myStudentId;
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    //QByteArray myToken="Bearer "+this->getWebToken();
    //request.setRawHeader(QByteArray("Authorization"),(myToken));
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

