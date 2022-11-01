#ifndef STUDENTWINDOW_H
#define STUDENTWINDOW_H

#include <QDialog>

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

private:
    Ui::StudentWindow *ui;
    QString webToken;
};

#endif // STUDENTWINDOW_H
