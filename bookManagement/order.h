#ifndef ORDER_H
#define ORDER_H

#include <QMainWindow>

namespace Ui {
class order;
}

class order : public QMainWindow
{
    Q_OBJECT

public:
    explicit order(QWidget *parent = nullptr);
    ~order();

private slots:
    void on_pushButton_back_clicked();

    void on_pushButton_show_clicked();

private:
    Ui::order *ui;
};

#endif // ORDER_H
