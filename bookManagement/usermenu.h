#ifndef USERMENU_H
#define USERMENU_H

#include <QMainWindow>

namespace Ui {
class userMenu;
}

class userMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit userMenu(QWidget *parent = nullptr);
    ~userMenu();

private slots:
    void on_pushButton_showBookList_clicked();

    void on_pushButton_basket_clicked();

    void on_pushButton_search_clicked();

    void on_pushButton_exit_clicked();

private:
    Ui::userMenu *ui;
};

#endif // USERMENU_H
