#ifndef BOOKLIST_H
#define BOOKLIST_H

#include <QMainWindow>

namespace Ui {
class bookList;
}

class bookList : public QMainWindow
{
    Q_OBJECT

public:
    explicit bookList(QWidget *parent = nullptr);
    ~bookList();

private slots:
    void on_pushButton_back_clicked();
    void openFileAndSortArray(const std::string& filePath, bool ascending, QString fileName);
    void on_pushButton_show_clicked();
    void showMsg(QString text, QString type);
    void on_pushButton_choose_clicked();
    void on_pushButton_basket_clicked();

    void on_pushButton_showall_clicked();

    void on_pushButton_clear_clicked();

private:
    Ui::bookList *ui;
};

#endif // BOOKLIST_H
