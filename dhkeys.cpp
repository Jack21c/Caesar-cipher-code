#include "dhkeys.h"
#include <math.h>
#include <QDebug>
#include <thread>

DiffieHellman::DiffieHellman(QObject *parent)
    : QObject(parent), a(-1), g(-1), p(-1) {}

void DiffieHellman::setA(int a_){
    a = a_;
}

void DiffieHellman::setB(int B){
    K = calc(B, a, p);
    emit sendK(K);
}

void DiffieHellman::setGP(int g_, int p_){
    g = g_;
    p = p_;
    emit sendGP(g, p);
    A = calc(g, a, p);
    emit sendA(A);
}

int DiffieHellman::calc(int x, int y, int mod){
    //int res = static_cast<int>(fmodf(powf(static_cast<float>(x), static_cast<float>(y)), static_cast<float>(mod)));
    //qDebug() << res;
    int xy = x%mod;
    int xx = x%mod;
    for(int i=2; i<=y; i++){
        xy = (xy*xx) % mod;
    }
    return xy;
}
