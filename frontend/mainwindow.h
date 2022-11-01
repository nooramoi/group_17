#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "studentwindow.h"
#include "myurl.h"

#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnLogin_clicked();
    void loginSlot (QNetworkReply *reply);

private:
    Ui::MainWindow *ui;
    StudentWindow *objectStudentWindow;
    QNetworkAccessManager *loginManager;
    QNetworkReply *reply;
    QByteArray response_data;
    QString id_student;
};
#endif // MAINWINDOW_H
