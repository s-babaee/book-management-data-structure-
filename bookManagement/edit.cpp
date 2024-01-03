#include "edit.h"
#include "ui_edit.h"
#include <adminMenu.h>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <addbook.h>

edit::edit(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::edit)
{
    ui->setupUi(this);
}

edit::~edit()
{
    delete ui;
}

void edit::on_pushButton_back_clicked()
{
    adminMenu *m = new adminMenu;
    m->show();
    this->hide();
}

void edit::showMsg(QString text, QString type){
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

void edit::on_pushButton_search_clicked()
{
    // Open the file
        QFile inputFile("../data/ISBN.txt");
        if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            return ;
        }

        bool find = false;
        // Read the file contents
        QTextStream in(&inputFile);
        int k = 0;
        while (!in.atEnd()) {
            QString line = in.readLine();
            k++;
            if(line == ui->lineEdit->text()){
                find = true;
                break;
            }
        }

        if(find){
            QFile outputFile("../data/edit.txt");
            if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
                return;
            }

            // Create a QTextStream object to write to the file
            QTextStream out(&outputFile);

            // Write data to the file
            out << k << endl;
            outputFile.close();

            addBook *m = new addBook;
            m->show();
            this->hide();
        }else{
            showMsg("No book was found with the desired ISBN.","Error");
        }

        inputFile.close();
}

