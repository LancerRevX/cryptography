QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TARGET = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    tabs/albertidisk.cpp \
    tabs/frequency_analysis/frequency_analysis.cpp \
    tabs/frequency_analysis/symbols_table_model.cpp \
    tabs/gronsveld.cpp \
    tabs/hill.cpp \
    tabs/playfair.cpp \
    tabs/richelieu.cpp \
    tabs/atbash.cpp \
    tabs/caesarcipher.cpp \
    tabs/cardangrille.cpp \
    tabs/polybiussquare.cpp \
    tabs/scytale.cpp \
    tabs/vernam.cpp \
    tabs/vigenere.cpp

HEADERS += \
    mainwindow.hpp \
    tabs/albertidisk.hpp \
    tabs/frequency_analysis/frequency_analysis.hpp \
    tabs/frequency_analysis/symbols_table_model.hpp \
    tabs/gronsveld.hpp \
    tabs/hill.hpp \
    tabs/playfair.hpp \
    tabs/richelieu.hpp \
    tabs/atbash.hpp \
    tabs/caesarcipher.hpp \
    tabs/cardangrille.hpp \
    tabs/polybiussquare.hpp \
    tabs/scytale.hpp \
    tabs/vernam.hpp \
    tabs/vigenere.hpp

FORMS += \
    mainwindow.ui \
    tabs/albertidisk.ui \
    tabs/frequency_analysis/frequency_analysis.ui \
    tabs/gronsveld.ui \
    tabs/hill.ui \
    tabs/playfair.ui \
    tabs/richelieu.ui \
    tabs/atbash.ui \
    tabs/caesarcipher.ui \
    tabs/cardangrille.ui \
    tabs/polybiussquare.ui \
    tabs/scytale.ui \
    tabs/vernam.ui \
    tabs/vigenere.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS += -L$$PWD/../ciphers/build-Debug/ -L$$PWD/../ciphers/matrix/ -lciphers -lmatrix

INCLUDEPATH += $$PWD/../ciphers
DEPENDPATH += $$PWD/../ciphers/build-Debug
PRE_TARGETDEPS += $$PWD/../ciphers/build-Debug/libciphers.a
