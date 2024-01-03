#include "booklist.h"
#include "ui_booklist.h"
#include <adminMenu.h>
#include <QtDebug>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <QMessageBox>
#include <QCoreApplication>
#include <QQueue>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <usermenu.h>


QString title, author, ISBN = "", price, number, longline, text;

bookList::bookList(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::bookList)
{
    ui->setupUi(this);
    ui->pushButton_choose->setEnabled(false);

    connect(ui->listWidget, &QListWidget::itemDoubleClicked, this, [this](QListWidgetItem *item) {
        ui->pushButton_choose->setText(" " + item->text());
        ui->pushButton_choose->setEnabled(true);
    });
}

bookList::~bookList()
{
    delete ui;
}

void bookList::showMsg(QString text, QString type){
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

void bookList::on_pushButton_back_clicked()
{
    // find user name
    QFile f("../data/user.txt");
    f.open(QFile::ReadOnly | QFile::Text);
    QTextStream in1(&f);
    QString user = in1.readLine();
    f.flush();
    f.close();

    if(user == "admin"){
        adminMenu *page = new adminMenu;
        page->show();
        this->hide();
    }else{
        userMenu *page = new userMenu;
        page->show();
        this->hide();
    }
}


///--------> sort
void bookList::on_pushButton_show_clicked()
{
    QString typeSort1 = ui->comboBox_sort1->currentText();
    bool ascending = (ui->comboBox_sort2->currentText() == "asc");

    ui->listWidget->clear();
    openFileAndSortArray("../data/" + typeSort1.toStdString() + ".txt", ascending, typeSort1);
}


///---------------------------------------------
int partition(std::vector<std::string>& arr, int low, int high, bool ascending) {
    std::string pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if ((ascending && arr[j] <= pivot) || (!ascending && arr[j] >= pivot)) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(std::vector<std::string>& arr, int low, int high, bool ascending) {
    if (low < high) {
        int pi = partition(arr, low, high, ascending);
        quickSort(arr, low, pi - 1, ascending);
        quickSort(arr, pi + 1, high, ascending);
    }
}

void bookList::openFileAndSortArray(const std::string& filePath, bool ascending, QString fileName) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cout << "Failed to open file: " << filePath << std::endl;
        return;
    }

    std::vector<std::string> numbers;
    std::vector<std::string> strings;
    std::string line;
    if (fileName == "number" || fileName == "price") {
        while (std::getline(file, line)) {
            numbers.push_back(line);
        }
        // Sort the number array using QuickSort
        quickSort(numbers, 0, numbers.size() - 1, ascending);

        for (const auto& number : numbers) {
            std::cout << number << std::endl;
            ui->listWidget->addItem(QString::fromStdString(number));
        }
    } else {
        while (std::getline(file, line)) {
            strings.push_back(line);
        }
        // Sort the string array using QuickSort
        quickSort(strings, 0, strings.size() - 1, ascending);

        for (const auto& str : strings) {
            std::cout << str << std::endl;
            ui->listWidget->addItem(QString::fromStdString(str));
        }
    }

    file.close();
}


void bookList::on_pushButton_choose_clicked()
{
    QString type = ui->comboBox_sort1->currentText(), select = ui->listWidget->currentItem()->text();
    bool find = false;
    QFile f("../data/BookList.txt");
    f.open(QFile::ReadOnly | QFile :: Text);
    QTextStream in(&f);
    longline = in.readLine();
    do {
        title = in.readLine();
        author = in.readLine();
        ISBN = in.readLine();
        price = in.readLine();
        number = in.readLine();
        longline = in.readLine();

        if(type == "title" && select == title){
            find = true;
            break;
        }
        if(type == "author" && select == author){
            find = true;
            break;
        }
        if(type == "ISBN" && select == ISBN){
            find = true;
            break;
        }
        if(type == "price" && select == price){
            find = true;
            break;
        }
        if(type == "number" && select == number){
            find = true;
            break;
        }
   } while (! longline.isNull() );
    f.close();

    if(find){
        text = "book name : " + title + "\n"
                     + "book author : " + author + "\n"
                     + "book ISBN : " + ISBN + "\n"
                     + "book price : " + price + "\n"
                     + "number of books : " + number;
        ui->plainTextEdit->setPlainText(text);
    }else{
        qDebug() << "error";
    }
}


void bookList::on_pushButton_basket_clicked()
{
    if(ISBN == ""){
        showMsg("No books selected!","Error");
        return;
    }

    // find user name
    QFile f("../data/user.txt");
    f.open(QFile::ReadOnly | QFile::Text);
    QTextStream in(&f);
    QString user = in.readLine();
    f.flush();
    f.close();

    // Create a queue of strings
        QQueue<QString> stringQueue;
        stringQueue.enqueue(text + "\n---------------------------");
        QFile file("../data/"+user+"/basket.txt");
            if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
                QTextStream out(&file);

                // Iterate over the queue and write each string to the file
                while (!stringQueue.isEmpty()) {
                    QString str = stringQueue.dequeue();
                    out << str << endl;
                }

                file.close();
                showMsg(title + " book has been successfully added to the shopping cart.", "Information");
            } else {
                showMsg("Failed to open file for writing.", "Error");
            }
}


void bookList::on_pushButton_showall_clicked()
{
    ui->plainTextEdit->clear();
    QFile inputFile("../data/BookList.txt");
    if (inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&inputFile);
        QString fileContent = in.readAll();
        ui->plainTextEdit->setPlainText(fileContent);
        inputFile.close();
    }
}


void bookList::on_pushButton_clear_clicked()
{
    ui->plainTextEdit->clear();
}

