#ifndef ADMINMENU_H
#define ADMINMENU_H

#include <QMainWindow>

namespace Ui {
class adminMenu;
}

class adminMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit adminMenu(QWidget *parent = nullptr);
    ~adminMenu();

private slots:
    void on_pushButton_addBook_clicked();

    void on_pushButton_showList_clicked();

    void on_pushButton_basket_clicked();

    void on_pushButton_order_clicked();

    void on_pushButton_edit_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_search_clicked();

private:
    Ui::adminMenu *ui;
};

#endif // ADMINMENU_H
