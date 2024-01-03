#include "adminmenu.h"
#include "ui_adminmenu.h"
#include <addbook.h>
#include <booklist.h>
#include <basket.h>
#include <order.h>
#include <edit.h>
#include <search.h>

adminMenu::adminMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::adminMenu)
{
    ui->setupUi(this);
}

adminMenu::~adminMenu()
{
    delete ui;
}

void adminMenu::on_pushButton_addBook_clicked()
{
    addBook *window = new addBook;
    window->show();
    this->hide();
}


void adminMenu::on_pushButton_showList_clicked()
{
    bookList *window = new bookList;
    window->show();
    this->hide();
}


void adminMenu::on_pushButton_basket_clicked()
{
    basket *window = new basket;
    window->show();
    this->hide();
}


void adminMenu::on_pushButton_order_clicked()
{
    order *window = new order;
    window->show();
    this->hide();
}


void adminMenu::on_pushButton_edit_clicked()
{
    edit *m = new edit;
    m->show();
    this->hide();
}


void adminMenu::on_pushButton_search_clicked()
{
    search *m = new search;
    m->show();
    this->hide();
}

