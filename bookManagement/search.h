#ifndef SEARCH_H
#define SEARCH_H

#include <QMainWindow>

namespace Ui {
class search;
}

class search : public QMainWindow
{
    Q_OBJECT

public:
    explicit search(QWidget *parent = nullptr);
    ~search();

private slots:
    void on_pushButton_back_clicked();
    void showMsg(QString text, QString type);
    void on_pushButton_search_clicked();

private:
    QString book(int n);
    Ui::search *ui;
};

#endif // SEARCH_H
