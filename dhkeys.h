#ifndef DIFFIEHELLMAN_H
#define DIFFIEHELLMAN_H

#include <QObject>

class DiffieHellman : public QObject
{
    Q_OBJECT
public:
    explicit DiffieHellman(QObject *parent = nullptr);


signals:
    void sendA(int);
    void sendGP(int, int);
    void sendK(int);

public slots:
    void setA(int a_);
    void setGP(int g_, int p_);
    void setB(int B);

private:
    int a;
    int A;
    int g;
    int p;
    int K;
    int calc(int, int, int);

};

#endif // DIFFIEHELLMAN_H
