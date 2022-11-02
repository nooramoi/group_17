#ifndef STUDENTWINDOW_H
#define STUDENTWINDOW_H

#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

namespace Ui {
class StudentWindow;
}

class StudentWindow : public QDialog
{
    Q_OBJECT

public:
    explicit StudentWindow(QString id_student,QWidget *parent = nullptr);
    ~StudentWindow();

    const QString &getWebToken() const;


    void setWebToken(const QByteArray &newWebToken);

private slots:
    void on_btnGrades_clicked();
    void gradeSlot (QNetworkReply *reply);
    void dataSlot (QNetworkReply *reply);

    void on_btnMyData_clicked();

private:
    Ui::StudentWindow *ui;
    QByteArray webToken;
    QString myStudentId;

    QNetworkAccessManager *gradeManager;
    QNetworkAccessManager *dataManager;
    QNetworkReply *reply;
    QByteArray response_data;
};

#endif // STUDENTWINDOW_H
