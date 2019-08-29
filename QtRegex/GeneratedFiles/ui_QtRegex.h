/********************************************************************************
** Form generated from reading UI file 'QtRegex.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTREGEX_H
#define UI_QTREGEX_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtRegexClass
{
public:
    QPushButton *pushButton;
    QLabel *label_2;
    QTextEdit *inputstring;
    QTextEdit *regexResult;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *regex;

    void setupUi(QWidget *QtRegexClass)
    {
        if (QtRegexClass->objectName().isEmpty())
            QtRegexClass->setObjectName(QStringLiteral("QtRegexClass"));
        QtRegexClass->resize(753, 540);
        pushButton = new QPushButton(QtRegexClass);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(50, 290, 93, 28));
        label_2 = new QLabel(QtRegexClass);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(50, 100, 111, 16));
        inputstring = new QTextEdit(QtRegexClass);
        inputstring->setObjectName(QStringLiteral("inputstring"));
        inputstring->setGeometry(QRect(50, 130, 671, 131));
        regexResult = new QTextEdit(QtRegexClass);
        regexResult->setObjectName(QStringLiteral("regexResult"));
        regexResult->setGeometry(QRect(50, 350, 671, 131));
        layoutWidget = new QWidget(QtRegexClass);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(50, 60, 681, 23));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        regex = new QLineEdit(layoutWidget);
        regex->setObjectName(QStringLiteral("regex"));

        horizontalLayout->addWidget(regex);


        retranslateUi(QtRegexClass);

        QMetaObject::connectSlotsByName(QtRegexClass);
    } // setupUi

    void retranslateUi(QWidget *QtRegexClass)
    {
        QtRegexClass->setWindowTitle(QApplication::translate("QtRegexClass", "QtRegex", Q_NULLPTR));
        pushButton->setText(QApplication::translate("QtRegexClass", "regex", Q_NULLPTR));
        label_2->setText(QApplication::translate("QtRegexClass", "input string\357\274\232", Q_NULLPTR));
        label->setText(QApplication::translate("QtRegexClass", "regex\357\274\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QtRegexClass: public Ui_QtRegexClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTREGEX_H
