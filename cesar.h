#ifndef CESAR_H
#define CESAR_H

#include <QObject>
#include <QString>

class Ces: public QObject
{
    Q_OBJECT
public:
    explicit Ces(QString ifn, QString ofn, int k, QObject *parent = nullptr) : QObject(parent), inFile(ifn), outFile(ofn), key(k){};
    void setInFile(QString fn);
    void setOutFile(QString fn);
    void setKey(int k);
    bool correctInput();
    void crypt(int koef);
    ~Ces();

signals:
    void problem(QString);

private:
    QString inFile;
    QString outFile;
    int key;
};

#endif // CESAR_H
