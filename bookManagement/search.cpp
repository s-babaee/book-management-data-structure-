#include "search.h"
#include "ui_search.h"
#include <QFile>
#include <QTextStream>
#include <adminMenu.h>
#include <usermenu.h>
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QTextStream>

search::search(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::search)
{
    ui->setupUi(this);
}

search::~search()
{
    delete ui;
}

void search::showMsg(QString text, QString type){
    QMessageBox msg(this);
    msg.setText(text);
    if(type == "Error"){
        msg.setIcon(QMessageBox::Critical);
        msg.setWindowTitle("ERROR");
        msg.setStyleSheet("background-color: #CF6679; border: none ;font-family: Arial"
                          "; font-style: normal;  font-size: 15pt; color: #000000 ;");
    }
    if(type == "Information"){
        msg.setIcon(QMessageBox::Information);
        msg.setWindowTitle("information");
        msg.setStyleSheet("background-color: #03DAC5; border: none ;font-family: Arial"
                          "; font-style: normal;  font-size: 15pt; color: rgb(255, 255, 255) ;");
    }
    msg.exec();
}

QString search::book(int n){
    QString str = "", line;
    QFile file("../data/BookList.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        for (int i = 1; i < (n-1) * 6 + 2; i++) {
           line = in.readLine();
        }
        for (int i = 1; i < 6; i++) {
            str += in.readLine() + "\n";
        }
        file.close();
    }
    return str;
}

void search::on_pushButton_back_clicked()
{
    // find user name
    QFile f("../data/user.txt");
    f.open(QFile::ReadOnly | QFile::Text);
    QTextStream in1(&f);
    QString user = in1.readLine();
    f.flush();
    f.close();

    if(user == "admin"){
            adminMenu *m = new adminMenu;
            m->show();
            this->hide();
        }else{
            userMenu *m = new userMenu;
            m->show();
            this->hide();
        }
}


void search::on_pushButton_search_clicked()
{
    ui->plainTextEdit->clear();
    if(ui->lineEdit->text().isEmpty()){
        showMsg("Please enter something in the search field.","Error");
        return;
    }

    QString key = ui->lineEdit->text();
    int i = 0;
    QHash<QString, QString> hashMap;

    QFile file("../data/ISBN.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            i++;
            hashMap.insert(in.readLine(), book(i));
        }
        file.close();
    }
    if (hashMap.contains(key)) {
                ui->plainTextEdit->setPlainText(hashMap.value(key));
        } else {
            showMsg("cant find this book!","Error");
        }
}

