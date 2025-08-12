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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton_ocultar;
    QPushButton *pushButton_mostrar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(20, 20);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButton_ocultar = new QPushButton(centralwidget);
        pushButton_ocultar->setObjectName(QString::fromUtf8("pushButton_ocultar"));
        pushButton_ocultar->setGeometry(QRect(0, 0, 20, 20));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        pushButton_ocultar->setFont(font);
        pushButton_ocultar->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_ocultar->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 165, 0);\n"
"border:1px solid #fff;;\n"
"color:#000;\n"
""));
        pushButton_mostrar = new QPushButton(centralwidget);
        pushButton_mostrar->setObjectName(QString::fromUtf8("pushButton_mostrar"));
        pushButton_mostrar->setGeometry(QRect(0, 0, 20, 20));
        pushButton_mostrar->setFont(font);
        pushButton_mostrar->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_mostrar->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 165, 0);\n"
"border:1px solid #fff;;\n"
"color:#000;\n"
""));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton_ocultar->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        pushButton_mostrar->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
