/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QGroupBox *groupBox;
    QPushButton *pushButton_login;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_2;
    QWidget *widget2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLineEdit *lineEdit_username;
    QWidget *widget3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QLineEdit *lineEdit_password;

    void setupUi(QDialog *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName(QStringLiteral("Login"));
        Login->resize(400, 300);
        groupBox = new QGroupBox(Login);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(0, 30, 401, 211));
        pushButton_login = new QPushButton(groupBox);
        pushButton_login->setObjectName(QStringLiteral("pushButton_login"));
        pushButton_login->setGeometry(QRect(90, 170, 211, 32));
        widget = new QWidget(groupBox);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(20, 70, 205, 23));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget1 = new QWidget(groupBox);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(20, 100, 198, 23));
        horizontalLayout_2 = new QHBoxLayout(widget1);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        widget2 = new QWidget(groupBox);
        widget2->setObjectName(QStringLiteral("widget2"));
        widget2->setGeometry(QRect(102, 70, 205, 23));
        horizontalLayout_3 = new QHBoxLayout(widget2);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget2);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_3->addWidget(label);

        lineEdit_username = new QLineEdit(widget2);
        lineEdit_username->setObjectName(QStringLiteral("lineEdit_username"));

        horizontalLayout_3->addWidget(lineEdit_username);

        widget3 = new QWidget(groupBox);
        widget3->setObjectName(QStringLiteral("widget3"));
        widget3->setGeometry(QRect(109, 100, 198, 23));
        horizontalLayout_4 = new QHBoxLayout(widget3);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(widget3);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_4->addWidget(label_2);

        lineEdit_password = new QLineEdit(widget3);
        lineEdit_password->setObjectName(QStringLiteral("lineEdit_password"));

        horizontalLayout_4->addWidget(lineEdit_password);


        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QDialog *Login)
    {
        Login->setWindowTitle(QApplication::translate("Login", "Dialog", nullptr));
        groupBox->setTitle(QApplication::translate("Login", "Sign-in", nullptr));
        pushButton_login->setText(QApplication::translate("Login", "Login", nullptr));
        label->setText(QApplication::translate("Login", "Username: ", nullptr));
        label_2->setText(QApplication::translate("Login", "Password:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
