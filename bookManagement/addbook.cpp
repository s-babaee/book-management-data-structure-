#include "addbook.h"
#include "ui_addbook.h"
#include <QMessageBox>
#include <adminmenu.h>
#include <QtDebug>
#include <QFile>

QString temp, k;
bool editMode = false;

addBook::addBook(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::addBook)
{
    ui->setupUi(this);

    QString filePath = "../data/edit.txt"; // Replace with your file path
        if (QFile::exists(filePath)) {
            editMode = true;
            ui->pushButton_add->setText("edit");
            ui->label->setText(" edit Book");
            QFile file(filePath);
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(&file);
                k = in.readLine();
                file.close();
                reaplace(k);
            }
            QFile::remove("../data/edit.txt");
        }
}

void addBook::reaplace(QString k){
    int n = k.toInt();
    QString line;
        QFile file("../data/BookList.txt");
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            for (int i = 1; i < (n-1)*6 + 2 ; i++) {
                line = in.readLine();
            }
            line = in.readLine();
            ui->lineEdit_title->setText(line);

            line = in.readLine();
            ui->lineEdit_aouthor->setText(line);

            line = in.readLine();
            ui->lineEdit_ISBN->setText(line);

            line = in.readLine();
            ui->lineEdit_price->setText(line);

            line = in.readLine();
            ui->lineEdit_number->setText(line);

            file.close();
        }

}

addBook::~addBook()
{
    delete ui;
}

void addBook::showMsg(QString text, QString type){
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

void addBook::on_pushButton_add_clicked()
{
    QString title = ui->lineEdit_title->text();
    QString author = ui->lineEdit_aouthor->text();
    QString ISBN = ui->lineEdit_ISBN->text();
    QString price = ui->lineEdit_price->text();
    QString number = ui->lineEdit_number->text();

    if(ISBN.isEmpty()){                                // test 1
                showMsg("Please enter your (ISBN book) in the relevant field.","Error");
                return;
            }

    if(title.isEmpty())
        title = "-";
    if(author.isEmpty())
        author = "-";
    if(price.isEmpty())
        title = "-";
    if(number.isEmpty())
        author = "-";

    // save in book list file
    saveInFile("title", title);
    saveInFile("author", author);
    saveInFile("ISBN", ISBN);
    saveInFile("price", price);
    saveInFile("number", number);

    saveInFile("BookList", title + "\n"
                        + author + "\n"
                        +  ISBN + "\n"
                        + price + "\n"
                        + number);
}

void addBook::saveInFile(QString fileName, QString txt){
    QFile file("../data/"+ fileName +".txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream stream(&file);

        if(fileName == "BookList")
            stream << "-------------------------------------\n";

        stream << txt << endl;
        file.close();

        if(fileName == "BookList"){
            showMsg("Your book has been successfully added.","Information");
            QString user = "admin";
            if(user == "admin"){
                adminMenu *page = new adminMenu;
                page->show();
                this->hide();
            }
        }

    }
    else if (fileName == "BookList")
        showMsg("error to open list book file!","Error");
}

void addBook::on_pushButton_back_clicked()
{
    QString user = "admin";
    if(user == "admin"){
        adminMenu *page = new adminMenu;
        page->show();
        this->hide();
    }
}

