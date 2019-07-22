/********************************************************************************
** Form generated from reading UI file 'ScreenCapture.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCREENCAPTURE_H
#define UI_SCREENCAPTURE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ScreenCaptureClass
{
public:
    QPushButton *capture;

    void setupUi(QWidget *ScreenCaptureClass)
    {
        if (ScreenCaptureClass->objectName().isEmpty())
            ScreenCaptureClass->setObjectName(QStringLiteral("ScreenCaptureClass"));
        ScreenCaptureClass->resize(600, 400);
        capture = new QPushButton(ScreenCaptureClass);
        capture->setObjectName(QStringLiteral("capture"));
        capture->setGeometry(QRect(100, 140, 93, 28));

        retranslateUi(ScreenCaptureClass);

        QMetaObject::connectSlotsByName(ScreenCaptureClass);
    } // setupUi

    void retranslateUi(QWidget *ScreenCaptureClass)
    {
        ScreenCaptureClass->setWindowTitle(QApplication::translate("ScreenCaptureClass", "ScreenCapture", Q_NULLPTR));
        capture->setText(QApplication::translate("ScreenCaptureClass", "capture", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ScreenCaptureClass: public Ui_ScreenCaptureClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCREENCAPTURE_H
