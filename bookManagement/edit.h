#ifndef EDIT_H
#define EDIT_H

#include <QMainWindow>

namespace Ui {
class edit;
}

class edit : public QMainWindow
{
    Q_OBJECT

public:
    explicit edit(QWidget *parent = nullptr);
    ~edit();

private slots:
    void on_pushButton_back_clicked();

    void showMsg(QString text, QString type);
    void on_pushButton_search_clicked();

private:
    Ui::edit *ui;
};

#endif // EDIT_H
