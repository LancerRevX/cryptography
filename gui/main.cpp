#include "mainwindow.hpp"

#include <QApplication>
#include <QDebug>
//#include <QRegExp>

#include <ciphers.hpp>

int main(int argc, char *argv[]) {
    QApplication aplication(argc, argv);
    MainWindow window;
    window.show();
    qDebug() << richelieu::encode(L"1234", {{1,2,4}});
    return aplication.exec();
}
