#include "dhwidget.h"
#include "ui_dhwidget.h"
#include <QErrorMessage>
#include <QTextBrowser>
#include <QIntValidator>
#include <limits.h>

DHWidget::DHWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DHWidget)
{
    ui->setupUi(this);
    alisa = new DiffieHellman();//создаем Алису
    bob = new DiffieHellman();//создаем Боба
    ui->input_a->setValidator(new QIntValidator(0, INT_MAX));
    ui->input_b->setValidator(new QIntValidator(0, INT_MAX));
    ui->input_g->setValidator(new QIntValidator(0, INT_MAX));
    ui->input_p->setValidator(new QIntValidator(0, INT_MAX));
    ui->showA->setStyleSheet("border: none; background-color: rgb(240, 240, 240);");//убираем границы и цвет поля,
    ui->showB->setStyleSheet("border: none; background-color: rgb(240, 240, 240);");//убираем границы и цвет поля,
    ui->showKAlisa->setStyleSheet("border: none; background-color: rgb(240, 240, 240);");//убираем границы и цвет поля,
    ui->showKBob->setStyleSheet("border: none; background-color: rgb(240, 240, 240);");//убираем границы и цвет поля,
    connect(alisa, &DiffieHellman::sendGP, bob, &DiffieHellman::setGP);
    connect(alisa, &DiffieHellman::sendA, bob, &DiffieHellman::setB);
    connect(bob, &DiffieHellman::sendA, alisa, &DiffieHellman::setB);
    connect(alisa, &DiffieHellman::sendA, [=](int A){
        ui->showA->setText(QString::number(A));
    });
    connect(bob, &DiffieHellman::sendA, [=](int B){
        ui->showB->setText(QString::number(B));
    });
    connect(alisa, &DiffieHellman::sendK, [=](int K){
        ui->showKAlisa->setText(QString::number(K));
    });
    connect(bob, &DiffieHellman::sendK, [=](int K){
        ui->showKBob->setText(QString::number(K));
    });

}

DHWidget::~DHWidget()
{
    delete ui;
}

void DHWidget::on_sendData_clicked()
{
    if(ui->input_a->displayText() != "" &&
            ui->input_g->displayText() != "" &&
            ui->input_p->displayText() != "" &&
            ui->input_b->displayText() != ""){
        int a = ui->input_a->displayText().toInt();
        alisa->setA(a);
        int b = ui->input_b->displayText().toInt();
        bob->setA(b);
        int g = ui->input_g->displayText().toInt();
        int p = ui->input_p->displayText().toInt();
        alisa->setGP(g, p);
    }
    else{
        QErrorMessage qem(this);
        qem.showMessage("Все поля должны быть заполнены!");
        qem.exec();
    }
}


void DHWidget::on_back_clicked()
{
    emit back(0);
}

