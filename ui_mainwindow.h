/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton_Start;
    QPushButton *pushButton_Stop;
    QPlainTextEdit *textEdit_Msg;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBox_ASCII;
    QCheckBox *checkBox_Hex;
    QCheckBox *checkBox_Save;
    QPushButton *pushButton_Clear;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        QFont font;
        font.setPointSize(13);
        MainWindow->setFont(font);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        pushButton_Start = new QPushButton(centralwidget);
        pushButton_Start->setObjectName(QStringLiteral("pushButton_Start"));
        pushButton_Start->setGeometry(QRect(200, 460, 121, 51));
        pushButton_Stop = new QPushButton(centralwidget);
        pushButton_Stop->setObjectName(QStringLiteral("pushButton_Stop"));
        pushButton_Stop->setGeometry(QRect(470, 460, 111, 51));
        textEdit_Msg = new QPlainTextEdit(centralwidget);
        textEdit_Msg->setObjectName(QStringLiteral("textEdit_Msg"));
        textEdit_Msg->setGeometry(QRect(31, 11, 731, 401));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(31, 421, 731, 33));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        checkBox_ASCII = new QCheckBox(widget);
        checkBox_ASCII->setObjectName(QStringLiteral("checkBox_ASCII"));

        horizontalLayout->addWidget(checkBox_ASCII);

        checkBox_Hex = new QCheckBox(widget);
        checkBox_Hex->setObjectName(QStringLiteral("checkBox_Hex"));

        horizontalLayout->addWidget(checkBox_Hex);

        checkBox_Save = new QCheckBox(widget);
        checkBox_Save->setObjectName(QStringLiteral("checkBox_Save"));

        horizontalLayout->addWidget(checkBox_Save);

        pushButton_Clear = new QPushButton(widget);
        pushButton_Clear->setObjectName(QStringLiteral("pushButton_Clear"));

        horizontalLayout->addWidget(pushButton_Clear);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 35));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        pushButton_Start->setText(QApplication::translate("MainWindow", "Start", Q_NULLPTR));
        pushButton_Stop->setText(QApplication::translate("MainWindow", "Stop", Q_NULLPTR));
        checkBox_ASCII->setText(QApplication::translate("MainWindow", "ASCII\346\216\245\346\224\266", Q_NULLPTR));
        checkBox_Hex->setText(QApplication::translate("MainWindow", "HEX\346\216\245\346\224\266", Q_NULLPTR));
        checkBox_Save->setText(QApplication::translate("MainWindow", "SaveToFiles", Q_NULLPTR));
        pushButton_Clear->setText(QApplication::translate("MainWindow", "Clear Window", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
