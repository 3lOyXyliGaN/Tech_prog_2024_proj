#include "FuncForCl.h"

FuncForCl::FuncForCl()
{
    client = Client::getInstance();

    ui_auth = new AuthandReg;
    ui_auth->show();
    connect(ui_auth, &AuthandReg::auth, this, &FuncForCl::sendAuth);
    connect(ui_auth, &AuthandReg::reg, this, &FuncForCl::sendReg);
    connect(client, &Client::MsgFromServer, this, &FuncForCl::msgHandler);;
}

void FuncForCl::sendAuth(QString log, QString pass)
{
    client->SendMsgToServer("auth&" + log + "&" + pass);
}

void FuncForCl::sendReg(QString log, QString pass, QString email)
{
    client->SendMsgToServer("reg&" + log + "&" + pass + "&" + email);
}

void FuncForCl::msgHandler(QString msg)
{
    if (msg == "Auth is successfully\r\n" || msg == "Reg is successfully\r\n")
    {
        delete ui_auth;
        ui_main = new Mainwindow;
        ui_main->show();

        connect(ui_main, &Mainwindow::RSA, this, &FuncForCl::solvRSA);
        connect(ui_main, &Mainwindow::hash, this, &FuncForCl::solvHash);

        connect(this, &FuncForCl::solv, ui_main, &Mainwindow::solv);
    }
    else
    {
        emit solv(msg);
    }
}

void FuncForCl::solvRSA(QString text)
{
    client->SendMsgToServer("rsa&" + text );
}

void FuncForCl::solvHash(QString text)
{
    client->SendMsgToServer("sha_512&" + text);
}

