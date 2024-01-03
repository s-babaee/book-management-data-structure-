#ifndef BASKET_H
#define BASKET_H

#include <QMainWindow>

namespace Ui {
class basket;
}

class basket : public QMainWindow
{
    Q_OBJECT

public:
    explicit basket(QWidget *parent = nullptr);
    ~basket();

private slots:
    void on_pushButton_back_clicked();
    void showMsg(QString text, QString type);
    void on_pushButton_buy_clicked();

private:
    Ui::basket *ui;
};

#endif // BASKET_H
