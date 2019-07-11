#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ImageGraphicsWindow.h"

class ImageGraphicsWindow : public QMainWindow
{
	Q_OBJECT

public:
	ImageGraphicsWindow(QWidget *parent = Q_NULLPTR);

	void buildConnect();

protected slots:
	virtual void onButtonClick();

protected:
	Ui::ImageGraphicsWindowClass ui;
};
