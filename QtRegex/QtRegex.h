#pragma once

#include <QtWidgets/QWidget>
#include "ui_QtRegex.h"

class QtRegex : public QWidget
{
	Q_OBJECT

public:
	QtRegex(QWidget *parent = Q_NULLPTR);
	void onRegex(bool);

private:
	Ui::QtRegexClass ui;
};
