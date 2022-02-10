#include "cesarwidget.h"
#include "ui_cesarwidget.h"
#include <QFileDialog>
#include "cesar.h"
#include <QIntValidator>
#include <QErrorMessage>

CesarWidget::CesarWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CesarWidget)
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

CesarWidget::~CesarWidget()
{
    delete ui;
}


void CesarWidget::on_openFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Выберите файл", QDir::currentPath(), "*.txt");
    //выбор текстового файла, вывод его в специальное поле и запись в экземпляр класса Ces
    if(fileName != "")
        ui->whatFile->setText(fileName);
    else
        ui->whatFile->setText("*Файл не выбран*");
    cesar->setInFile(fileName);
}


void CesarWidget::on_encrypt_clicked()
{
    int k = ui->keyInput->displayText().toInt();
    cesar->setKey(k);//запись величины сдвига в экземпляр класса Ces
    if(cesar->correctInput()){//если все необходимые данные получены, выбираем, в какой файл записать ответ
        QString fileName = QFileDialog::getSaveFileName(this, "Сохранение файла", QDir::currentPath(), "*.txt");
        cesar->setOutFile(fileName);
        cesar->crypt(1);//шифруем
    }
}


void CesarWidget::on_decrypt_clicked()
{
    int k = ui->keyInput->displayText().toInt();
    cesar->setKey(k);//запись величины сдвига в экземпляр класса Ces
    if(cesar->correctInput()){//если все необходимые данные получены, выбираем, в какой файл записать ответ
        QString fileName = QFileDialog::getSaveFileName(this, "Сохранение файла", QDir::currentPath(), "*.txt");
        cesar->setOutFile(fileName);
        cesar->crypt(-1);//дешифруем
    }
}


void CesarWidget::on_back_clicked()
{
    emit back(0);
}

