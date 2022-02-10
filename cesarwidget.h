#ifndef CESARWIDGET_H
#define CESARWIDGET_H

#include <QWidget>
#include "cesar.h"

namespace Ui {
class CesarWidget;
}

class CesarWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CesarWidget(QWidget *parent = nullptr);
    ~CesarWidget();
signals:
    void back(int);

private slots:
    void on_openFile_clicked();

    void on_encrypt_clicked();

    void on_decrypt_clicked();

    void on_back_clicked();

private:
    Ui::CesarWidget *ui;
    Ces *cesar;
};

#endif // CESARWIDGET_H
