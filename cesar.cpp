#include "cesar.h"
#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include <QString>

void Ces::crypt(int koef){
    QFile fr(inFile);
    QFile fw(outFile);
    if (!fr.open(QIODevice::ReadOnly)) {//открываем файл для чтения
        emit problem("Cannot open file for reading");
    }
    else if (!fw.open(QIODevice::WriteOnly | QIODevice::Text)) {//открываем другой файл для записи
        emit problem("Cannot open file for writing");
    }
    else{//шифруем/дешифруем, в зависимости от переданного коэффициента
        QTextStream in(&fr);
        QTextStream out(&fw);
        QChar cr;
        QString inLine, outLine;
        int num;
        bool firstEnter = true;
        while (!in.atEnd()) {
            if(firstEnter)
                firstEnter = false;
            else
                out << "\n";
            inLine = in.readLine();
            outLine = "";
            for(int i = 0; i < inLine.length(); i++){
                cr = inLine.at(i);
                if(cr.isLetter()){
                    num = static_cast<int>(cr.unicode());
                    if(num < 95){
                        num += koef*key - 65;
                        while(num < 0)
                            num += 26;
                        while(num >= 26)
                            num -= 26;
                        num += 65;
                    }
                    else if(num < 128){
                        num += koef*key - 97;
                        while(num < 0)
                            num += 26;
                        while(num >= 26)
                            num -= 26;
                        num += 97;
                    }
                    else{
                        if(num == 1025)
                            num = 1045;
                        if(num == 1105)
                            num = 1077;
                        if(num >= 1040 && num <= 1071){
                            num += koef*key - 1040;
                            while(num < 0)
                                num += 32;
                            while(num >= 32)
                                num -= 32;
                            num += 1040;
                        }
                        else if(num >= 1072 && num <= 1103){
                            num += koef*key - 1072;
                            while(num < 0)
                                num += 32;
                            while(num >= 32)
                                num -= 32;
                            num += 1072;
                        }
                    }
                    QChar cw(num);
                    outLine.append(cw);
                }
                else{
                    outLine.append(cr);
                }
            }
            out << outLine;
        }
        fr.close();
        fw.close();
    }
}

void Ces::setInFile(QString fn){//записываем адрес файла для чтения
    inFile = fn;
}

void Ces::setOutFile(QString fn){//записываем адрес файла для записи
    outFile = fn;
}

void Ces::setKey(int k){//записываем величину сдвига
    key = k;
}

bool Ces::correctInput(){//проверяем, правда ли, что файл для чтения и величина сдвига указаны
    if(inFile == "" && key == 0){
        emit problem("Выберите файл и укажите величину сдвига");
    }
    else if(inFile == ""){
        emit problem("Выберите файл");
    }
    else if(key == 0){
        emit problem("Укажите величину сдвига");
    }
    else{
        return true;
    }
    return false;
}

Ces::~Ces(){}
