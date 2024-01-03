#ifndef ADDBOOK_H
#define ADDBOOK_H

#include <QMainWindow>

namespace Ui {
class addBook;
}

class addBook : public QMainWindow
{
    Q_OBJECT

public:
    explicit addBook(QWidget *parent = nullptr);
    ~addBook();

private slots:
    void on_pushButton_add_clicked();
    void showMsg(QString text, QString type);
    void saveInFile(QString fileName, QString txt);
    void on_pushButton_back_clicked();
    void reaplace(QString k);

private:
    Ui::addBook *ui;
};

#endif // ADDBOOK_H
