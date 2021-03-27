QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TARGET = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    tabs/atbash.cpp \
    tabs/polybiussquare.cpp \
    tabs/scytale.cpp

HEADERS += \
    mainwindow.hpp \
    tabs/atbash.hpp \
    tabs/polybiussquare.hpp \
    tabs/scytale.hpp

FORMS += \
    mainwindow.ui \
    tabs/atbash.ui \
    tabs/polybiussquare.ui \
    tabs/scytale.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS += -L$$PWD/../ciphers/build-ciphers-Desktop_Qt_5_15_2_MinGW_64_bit-Debug/ -lciphers

INCLUDEPATH += $$PWD/../ciphers
DEPENDPATH += $$PWD/../ciphers
PRE_TARGETDEPS += $$PWD/../ciphers/build-ciphers-Desktop_Qt_5_15_2_MinGW_64_bit-Debug/libciphers.a
