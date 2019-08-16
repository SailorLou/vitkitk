#pragma once

#include <QWidget>
#include "ui_ScreenCapture.h"

class GrabManager;
class ScreenCapture : public QWidget
{
	Q_OBJECT

public:
	ScreenCapture(QWidget *parent = Q_NULLPTR);
protected slots:
	void OnCapture(bool checked);

private:
	Ui::ScreenCaptureClass ui;
	GrabManager *_grabber;//todo:smart pointer
};
