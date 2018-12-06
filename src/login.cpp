#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include <iostream>


Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_login_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();


    if(username == QString("admin") && password == QString("password"))
    {
        accept();
    }
    else
    {
        QMessageBox::warning(this, "Login", "Username or Password is incorrect");
    }
}
