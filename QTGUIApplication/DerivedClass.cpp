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
	auto text1 = ui.lineEdit->text();
	ui.lineEdit->setText("");
	auto text = ui.lineEdit->text();
	auto distext = ui.lineEdit->displayText();
	int i = 9;
}
