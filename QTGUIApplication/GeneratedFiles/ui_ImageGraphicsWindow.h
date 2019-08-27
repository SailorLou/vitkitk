/********************************************************************************
** Form generated from reading UI file 'ImageGraphicsWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEGRAPHICSWINDOW_H
#define UI_IMAGEGRAPHICSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImageGraphicsWindowClass
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QWidget *widget;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QLineEdit *lineEdit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QButtonGroup *buttonGroup;

    void setupUi(QMainWindow *ImageGraphicsWindowClass)
    {
        if (ImageGraphicsWindowClass->objectName().isEmpty())
            ImageGraphicsWindowClass->setObjectName(QStringLiteral("ImageGraphicsWindowClass"));
        ImageGraphicsWindowClass->resize(686, 400);
        centralWidget = new QWidget(ImageGraphicsWindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        buttonGroup = new QButtonGroup(ImageGraphicsWindowClass);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(pushButton);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(200, 150, 93, 28));
        pushButton->setCheckable(true);
        pushButton_2 = new QPushButton(centralWidget);
        buttonGroup->addButton(pushButton_2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(350, 150, 93, 28));
        pushButton_2->setCheckable(true);
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(40, 80, 141, 111));
        pushButton_3->setCheckable(false);
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(150, 230, 401, 80));
        widget->setAutoFillBackground(false);
        widget->setStyleSheet(QLatin1String("* {\n"
"    background-color:#041D32;\n"
"}"));
        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(300, 50, 91, 19));
        checkBox_2 = new QCheckBox(centralWidget);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));
        checkBox_2->setGeometry(QRect(410, 50, 91, 19));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(510, 150, 113, 21));
        ImageGraphicsWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ImageGraphicsWindowClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 686, 26));
        ImageGraphicsWindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ImageGraphicsWindowClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ImageGraphicsWindowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ImageGraphicsWindowClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ImageGraphicsWindowClass->setStatusBar(statusBar);

        retranslateUi(ImageGraphicsWindowClass);

        QMetaObject::connectSlotsByName(ImageGraphicsWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *ImageGraphicsWindowClass)
    {
        ImageGraphicsWindowClass->setWindowTitle(QApplication::translate("ImageGraphicsWindowClass", "ImageGraphicsWindow", Q_NULLPTR));
        pushButton->setText(QApplication::translate("ImageGraphicsWindowClass", "PushButton", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("ImageGraphicsWindowClass", "PushButton", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("ImageGraphicsWindowClass", "PushButton", Q_NULLPTR));
        checkBox->setText(QApplication::translate("ImageGraphicsWindowClass", "CheckBox", Q_NULLPTR));
        checkBox_2->setText(QApplication::translate("ImageGraphicsWindowClass", "CheckBox", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ImageGraphicsWindowClass: public Ui_ImageGraphicsWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEGRAPHICSWINDOW_H
