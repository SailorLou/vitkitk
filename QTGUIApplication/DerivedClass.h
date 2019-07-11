#pragma once

#include "ImageGraphicsWindow.h"
class DerivedClass:public ImageGraphicsWindow
{
	Q_OBJECT
public:
	DerivedClass(QWidget *parent = Q_NULLPTR);
	~DerivedClass();
protected slots:
	void onButtonClick() override;
};

