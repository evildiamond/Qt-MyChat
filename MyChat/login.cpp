#include "login.h"
#include "ui_login.h"

#include<QMessageBox>

Login::Login(unsigned int*id,QWidget *parent) :
    QDialog(parent),
    id(id),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_loginButton_clicked()
{
    if(ui->idLineEdit->text().isEmpty()||ui->passwordLineEdit->text().isEmpty()){
        QMessageBox::warning(this,tr("请输入账号密码！"),tr("请输入账号密码！"),QMessageBox::Ok);
        return;
    }
    bool check;
    *id=ui->idLineEdit->text().toUInt(&check);
    if(check){
        QDialog::accept();
    }
    else{
        QMessageBox::warning(this,tr("账号或密码错误！"),tr("账号或密码错误"),QMessageBox::Ok);
    }
}

void Login::on_cancelButton_clicked()
{
    QDialog::reject();
}
