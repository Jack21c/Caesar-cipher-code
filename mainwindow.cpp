#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStackedWidget>
#include "cesarwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    ui->sWidget->insertWidget(1, &cw);
    ui->sWidget->insertWidget(2, &dhw);
    connect(&cw, &CesarWidget::back, ui->sWidget, &QStackedWidget::setCurrentIndex);
    connect(&dhw, &DHWidget::back, ui->sWidget, &QStackedWidget::setCurrentIndex);
    //ui->stackedWidget->addWidget(cw);
    //ui->stackedWidget->insertWidget(1, cw);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_cesarButton_clicked()
{
    ui->sWidget->setCurrentIndex(1);
}


void MainWindow::on_dhButton_clicked()
{
    ui->sWidget->setCurrentIndex(2);
}

