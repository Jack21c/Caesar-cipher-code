#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSignalMapper>
#include <QFileDialog>
#include "cesar.h"
#include <QIntValidator>
#include <QErrorMessage>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cesar = new Ces("", "", 0);
    ui->keyInput->setValidator(new QIntValidator(0, 33));
    ui->whatFile->setText("*Файл не выбран*");//первоначальный текст в поле, где выводится адрес выбранного файла
    ui->whatFile->setStyleSheet("border: none; background-color: rgb(240, 240, 240);");//убираем границы и цвет поля,
    //где выводится адрес выбранного файла, чтобы пользователь не пытался его редактировать
    connect(cesar, &Ces::problem, [=](QString s){//в случае ошибки будет показано окно с сообщением об ошибке
        QErrorMessage qem(this);
        qem.showMessage(s);
        qem.exec();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openFile_triggered()//обработка нажатия на кнопку "Открыть файл"
{
    QString fileName = QFileDialog::getOpenFileName(this, "Выберите файл", QDir::currentPath(), "*.txt");
    //выбор текстового файла, вывод его в специальное поле и запись в экземпляр класса Ces
    if(fileName != "")
        ui->whatFile->setText(fileName);
    else
        ui->whatFile->setText("*Файл не выбран*");
    cesar->setInFile(fileName);
}

void MainWindow::on_encrypt_triggered()//обработка нажатия на кнопку "Зашифровать"
{
    int k = ui->keyInput->displayText().toInt();
    cesar->setKey(k);//запись величины сдвига в экземпляр класса Ces
    if(cesar->correctInput()){//если все необходимые данные получены, выбираем, в какой файл записать ответ
        QString fileName = QFileDialog::getSaveFileName(this, "Сохранение файла", QDir::currentPath(), "*.txt");
        cesar->setOutFile(fileName);
        cesar->crypt(1);//шифруем
    }
}

void MainWindow::on_decrypt_triggered()//обработка нажатия на кнопку "Дешифровать"
{
    int k = ui->keyInput->displayText().toInt();
    cesar->setKey(k);//запись величины сдвига в экземпляр класса Ces
    if(cesar->correctInput()){//если все необходимые данные получены, выбираем, в какой файл записать ответ
        QString fileName = QFileDialog::getSaveFileName(this, "Сохранение файла", QDir::currentPath(), "*.txt");
        cesar->setOutFile(fileName);
        cesar->crypt(-1);//дешифруем
    }
}
