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
    void setWebToken(const QString &newWebToken);

private slots:
    void on_btnGrades_clicked();
    void gradeSlot (QNetworkReply *reply);

private:
    Ui::StudentWindow *ui;
    QString webToken;
    QString myStudentId;

    QNetworkAccessManager *gradeManager;
    QNetworkReply *reply;
    QByteArray response_data;
};

#endif // STUDENTWINDOW_H
