/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include "tabs/atbashtab.hpp"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    AtbashTab *atbashTab;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(606, 266);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(606, 266));
        MainWindow->setMaximumSize(QSize(606, 266));
        MainWindow->setIconSize(QSize(16, 16));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(20, 20, 566, 226));
        tabWidget->setFocusPolicy(Qt::NoFocus);
        atbashTab = new AtbashTab();
        atbashTab->setObjectName(QString::fromUtf8("atbashTab"));
        tabWidget->addTab(atbashTab, QString());
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\232\321\200\320\270\320\277\321\202\320\276\320\263\321\200\320\260\321\204\320\270\321\207\320\265\321\201\320\272\320\270\320\265 \320\274\320\265\321\202\320\276\320\264\321\213 \320\267\320\260\321\211\320\270\321\202\321\213 \320\270\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\320\270, \320\235.\320\220.\320\232\320\270\321\200\320\265\320\275\320\272\320\276\320\262, \320\232\320\23017-01", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(atbashTab), QCoreApplication::translate("MainWindow", "\320\220\321\202\320\261\320\260\321\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
