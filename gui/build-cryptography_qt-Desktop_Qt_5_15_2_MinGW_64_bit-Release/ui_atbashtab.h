/********************************************************************************
** Form generated from reading UI file 'atbashtab.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ATBASHTAB_H
#define UI_ATBASHTAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AtbashTab
{
public:
    QLineEdit *messageEdit;
    QPushButton *switchButton;
    QLabel *messageLabel;
    QLabel *codeLabel;
    QLineEdit *codeEdit;

    void setupUi(QWidget *AtbashTab)
    {
        if (AtbashTab->objectName().isEmpty())
            AtbashTab->setObjectName(QString::fromUtf8("AtbashTab"));
        AtbashTab->resize(560, 100);
        messageEdit = new QLineEdit(AtbashTab);
        messageEdit->setObjectName(QString::fromUtf8("messageEdit"));
        messageEdit->setGeometry(QRect(110, 20, 390, 20));
        QFont font;
        font.setFamily(QString::fromUtf8("Courier"));
        messageEdit->setFont(font);
        switchButton = new QPushButton(AtbashTab);
        switchButton->setObjectName(QString::fromUtf8("switchButton"));
        switchButton->setGeometry(QRect(520, 19, 22, 62));
        QFont font1;
        font1.setPointSize(16);
        switchButton->setFont(font1);
        messageLabel = new QLabel(AtbashTab);
        messageLabel->setObjectName(QString::fromUtf8("messageLabel"));
        messageLabel->setGeometry(QRect(20, 20, 70, 20));
        messageLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        codeLabel = new QLabel(AtbashTab);
        codeLabel->setObjectName(QString::fromUtf8("codeLabel"));
        codeLabel->setGeometry(QRect(20, 60, 70, 20));
        codeLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        codeEdit = new QLineEdit(AtbashTab);
        codeEdit->setObjectName(QString::fromUtf8("codeEdit"));
        codeEdit->setGeometry(QRect(110, 60, 390, 20));
        codeEdit->setFont(font);
        codeEdit->setReadOnly(true);
        QWidget::setTabOrder(messageEdit, codeEdit);
        QWidget::setTabOrder(codeEdit, switchButton);

        retranslateUi(AtbashTab);

        QMetaObject::connectSlotsByName(AtbashTab);
    } // setupUi

    void retranslateUi(QWidget *AtbashTab)
    {
        AtbashTab->setWindowTitle(QCoreApplication::translate("AtbashTab", "Form", nullptr));
        messageEdit->setText(QString());
        switchButton->setText(QCoreApplication::translate("AtbashTab", "\342\207\205", nullptr));
        messageLabel->setText(QCoreApplication::translate("AtbashTab", "\320\241\320\276\320\276\320\261\321\211\320\265\320\275\320\270\320\265", nullptr));
        codeLabel->setText(QCoreApplication::translate("AtbashTab", "\320\232\320\276\320\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AtbashTab: public Ui_AtbashTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ATBASHTAB_H
