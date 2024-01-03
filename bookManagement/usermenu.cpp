#include "usermenu.h"
#include "ui_usermenu.h"
#include <basket.h>
#include <booklist.h>
#include <search.h>

userMenu::userMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::userMenu)
{
    ui->setupUi(this);
}

userMenu::~userMenu()
{
    delete ui;
}

void userMenu::on_pushButton_showBookList_clicked()
{
    bookList *m = new bookList;
    m->show();
    this->hide();
}


void userMenu::on_pushButton_basket_clicked()
{
    basket *m = new basket;
    m->show();
    this->hide();
}





void userMenu::on_pushButton_search_clicked()
{
    search *m = new search;
    m->show();
    this->hide();
}

