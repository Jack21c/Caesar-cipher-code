#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cesar.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_openFile_triggered();



    void on_encrypt_triggered();

    void on_decrypt_triggered();

private:
    Ui::MainWindow *ui;
    Ces *cesar;
};
#endif // MAINWINDOW_H
