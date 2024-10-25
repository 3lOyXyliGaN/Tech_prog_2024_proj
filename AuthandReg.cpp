#include "AuthandReg.h"
#include "ui_AuthandReg.h"

AuthandReg::AuthandReg(QWidget *parent) : QWidget(parent), ui(new Ui::AuthandReg)
{
    ui->setupUi(this);
    ui->mail->setVisible(false);
    ui->regis->setVisible(false);
    ui->regbutton->setVisible(false);
    ui->enter->setVisible(false);
}

AuthandReg::~AuthandReg()
{
    delete ui;
}


void AuthandReg::on_authbutton_clicked()
{
    // Обработка авторизации
    emit auth(ui->login->text(), ui->password->text());
}


void AuthandReg::on_regbutton_clicked()
{
    emit reg(ui->login->text(), ui->password->text(),ui->mail->text());
}


void AuthandReg::on_makeacc_clicked()
{
    ui->mail->setVisible(true);
    ui->regis->setVisible(true);
    ui->regbutton->setVisible(true);
    ui->enter->setVisible(true);

    ui->authoriz->setVisible(false);
    ui->authbutton->setVisible(false);
    ui->makeacc->setVisible(false);
}


void AuthandReg::on_enter_clicked()
{
    ui->authoriz->setVisible(true);
    ui->authbutton->setVisible(true);
    ui->makeacc->setVisible(true);

    ui->mail->setVisible(false);
    ui->regis->setVisible(false);
    ui->regbutton->setVisible(false);
    ui->enter->setVisible(false);
}

