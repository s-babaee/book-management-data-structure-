#include "basket.h"
#include "ui_basket.h"
#include <QFile>
#include <adminMenu.h>
#include <usermenu.h>
#include <QTextStream>
#include <QQueue>
#include <QString>
#include <QDebug>
#include <QMessageBox>

QString user;

basket::basket(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::basket)
{
    ui->setupUi(this);

    // find user name
    QFile f("../data/user.txt");
    f.open(QFile::ReadOnly | QFile::Text);
    QTextStream in1(&f);
    user = in1.readLine();
    f.flush();
    f.close();

    // Open the file for reading
        QFile inputFile("../data/"+ user +"/basket.txt");
            if (inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(&inputFile);
                QString fileContent = in.readAll();
                inputFile.close();

                // Display the file contents in the QPlainTextEdit widget
                ui->plainTextEdit->setPlainText(fileContent);
            }
}

basket::~basket()
{
    delete ui;
}

void basket::showMsg(QString text, QString type){
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

void basket::on_pushButton_back_clicked()
{

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

void basket::on_pushButton_buy_clicked()
{
    QString text = ui->plainTextEdit->toPlainText();
    if (text.isEmpty()) {
        showMsg("The besket is empty.","Error");
        return;
    }
    QFile file("../data/"+ user +"/basket.txt");
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QQueue<QString> stringQueue;
            QTextStream in(&file);

            // Read lines from the file and enqueue them into the queue
            while (!in.atEnd()) {
                QString line = in.readLine();
                stringQueue.enqueue(line);
            }

            file.close();
            qDebug() << "File data read and populated into the queue.";

            // Clear the file
            if (file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
                file.close();

            // Create a new file and save the data from the queue
            QFile newFile("../data/order.txt");
            if (newFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
                QTextStream out(&newFile);

                // Save the queue data to the new file
                out << "**************************************\n"
                    <<  "[user : " + user + " ]\n"
                    << "**************************************\n";
                while (!stringQueue.isEmpty()) {
                    QString line = stringQueue.dequeue();
                    out << line + "\n";
                }
                out << "**************************************\n"
                    << "**************************************\n\n";

                newFile.close();
                showMsg("Your orders have been successfully registered.", "Information");
            } else {
                showMsg("Unfortunately, your order was not registered.", "Error");
            }
        }
        ui->plainTextEdit->clear();
}

