#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_pushButton_login_clicked();

    void on_pushButton_signup_clicked();

    void sign_up();
    bool test_user(QString user);
    bool test_pass(QString pass);
    void log_in();
    bool find_user(QString user, QString pass);
    void showMsg(QString text, QString type);

    void on_pushButton_SIGNUP_clicked();

    void on_pushButton_LOGIN_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
