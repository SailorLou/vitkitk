/********************************************************************************
** Form generated from reading UI file 'QtImageViewer.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTIMAGEVIEWER_H
#define UI_QTIMAGEVIEWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtImageViewerClass
{
public:

    void setupUi(QWidget *QtImageViewerClass)
    {
        if (QtImageViewerClass->objectName().isEmpty())
            QtImageViewerClass->setObjectName(QStringLiteral("QtImageViewerClass"));
        QtImageViewerClass->resize(600, 400);

        retranslateUi(QtImageViewerClass);

        QMetaObject::connectSlotsByName(QtImageViewerClass);
    } // setupUi

    void retranslateUi(QWidget *QtImageViewerClass)
    {
        QtImageViewerClass->setWindowTitle(QApplication::translate("QtImageViewerClass", "QtImageViewer", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QtImageViewerClass: public Ui_QtImageViewerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTIMAGEVIEWER_H
