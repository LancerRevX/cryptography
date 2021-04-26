#include "mainwindow.hpp"

#include <QApplication>
#include <QDebug>
//#include <QRegExp>

#include <ciphers.hpp>

int main(int argc, char *argv[]) {
    QApplication aplication(argc, argv);
    MainWindow window;
    window.show();
    return aplication.exec();
}
