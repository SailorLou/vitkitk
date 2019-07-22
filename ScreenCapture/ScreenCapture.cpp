#include "ScreenCapture.h"
#include<QPushButton>

#include "GrabManager.h"

ScreenCapture::ScreenCapture(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	_grabber = new GrabManager(this);

	connect(ui.capture, &QPushButton::clicked, this, &ScreenCapture::OnCapture);
}


void ScreenCapture::OnCapture(bool check)
{
	_grabber->grab(GrabManager::GRAB_RECTANGULAR_REGION);
}