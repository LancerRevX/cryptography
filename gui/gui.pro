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
    tabs/richelieu.cpp \
    tabs/atbash.cpp \
    tabs/caesarcipher.cpp \
    tabs/cardangrille.cpp \
    tabs/polybiussquare.cpp \
    tabs/scytale.cpp

HEADERS += \
    mainwindow.hpp \
    tabs/richelieu.hpp \
    tabs/atbash.hpp \
    tabs/caesarcipher.hpp \
    tabs/cardangrille.hpp \
    tabs/polybiussquare.hpp \
    tabs/scytale.hpp

FORMS += \
    mainwindow.ui \
    tabs/richelieu.ui \
    tabs/atbash.ui \
    tabs/caesarcipher.ui \
    tabs/cardangrille.ui \
    tabs/polybiussquare.ui \
    tabs/scytale.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS += -L$$PWD/../ciphers/ -lciphers

INCLUDEPATH += $$PWD/../ciphers
DEPENDPATH += $$PWD/../ciphers
PRE_TARGETDEPS += $$PWD/../ciphers/libciphers.a
