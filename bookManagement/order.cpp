#include "order.h"
#include "ui_order.h"
#include <QFile>
#include <QTextStream>
#include <adminMenu.h>
#include <usermenu.h>

QString user1;

order::order(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::order)
{
    ui->setupUi(this);
    // find user name
    QFile f("../data/user.txt");
    f.open(QFile::ReadOnly | QFile::Text);
    QTextStream in1(&f);
    user1 = in1.readLine();
    f.flush();
    f.close();

    // Open the file for reading
        QFile inputFile("../data/order.txt");
            if (inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(&inputFile);
                QString fileContent = in.readAll();
                inputFile.close();

                // Display the file contents in the QPlainTextEdit widget
                ui->plainTextEdit->setPlainText(fileContent);
            }
}

order::~order()
{
    delete ui;
}

void order::on_pushButton_back_clicked()
{
    if(user1 == "admin"){
            adminMenu *m = new adminMenu;
            m->show();
            this->hide();
        }else{
            userMenu *m = new userMenu;
            m->show();
            this->hide();
        }
}


