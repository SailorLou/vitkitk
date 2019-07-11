#include "DerivedClass.h"

#include "ImageGraphicsWindow.h"

DerivedClass::DerivedClass(QWidget *parent):ImageGraphicsWindow(parent)
{
	setWindowTitle("derive");
}


DerivedClass::~DerivedClass()
{

}

void DerivedClass::onButtonClick()
{
	ui.pushButton_3->setText("derivedclass");
}
