#include "Mainwindow.h"
#include "ui_Mainwindow.h"

Mainwindow::Mainwindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::Mainwindow)
{
    ui->setupUi(this);

    currentTask = rsa;
    ui->Header->setText("RSA");
    ui->arg1->setPlaceholderText("Текст");
    ui->Answer->setText("");
}

Mainwindow::~Mainwindow()
{
    delete ui;
}


void Mainwindow::solv(QString text)
{
    ui->Answer->setText(text);
}
void Mainwindow::on_Solve_clicked()
{
    if (currentTask == rsa)
    {
        emit RSA(ui->arg1->text());
    }
    else if (currentTask == sha512)
    {
        emit hash(ui->arg1->text());
    }
}

void Mainwindow::on_Change_clicked()
{
    if (currentTask == rsa)
    {
        currentTask = sha512;
        ui->Header->setText("Sha-512");
        ui->arg1->setPlaceholderText("Строка");
        ui->Answer->setText("");
    }
    else if (currentTask == sha512)
    {
        currentTask = rsa;
        ui->Header->setText("RSA");
        ui->arg1->setPlaceholderText("Текст");
        ui->Answer->setText("");
    }
}

