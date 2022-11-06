#ifndef STUDENTEDIT_H
#define STUDENTEDIT_H

#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

namespace Ui {
class StudentEdit;
}

class StudentEdit : public QDialog
{
    Q_OBJECT

public:
    explicit StudentEdit(QByteArray wt, QString fn, QString ln, QString id,QWidget *parent = nullptr);
    ~StudentEdit();



private slots:
    void on_btnSave_clicked();

    void on_btnCancel_clicked();
    void updateStudentSlot (QNetworkReply *reply);

private:
    Ui::StudentEdit *ui;
    QByteArray webToken;
    QString fname;
    QString lname;
    QString id_student;
    QNetworkAccessManager *updateManager;
    QNetworkReply *reply;
    QByteArray response_data;
};

#endif // STUDENTEDIT_H
