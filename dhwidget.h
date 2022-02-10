#ifndef DHWIDGET_H
#define DHWIDGET_H

#include <QWidget>
#include "dhkeys.h"

namespace Ui {
class DHWidget;
}

class DHWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DHWidget(QWidget *parent = nullptr);
    ~DHWidget();
signals:
    void back(int);

private slots:
    void on_sendData_clicked();

    void on_back_clicked();

private:
    Ui::DHWidget *ui;
    DiffieHellman *alisa;
    DiffieHellman *bob;
};

#endif // DHWIDGET_H
