#pragma once
#include <qwidget.h>
class QLabel;
class QScrollArea;
class QImage;
class QScrollBar;
class QImageViewerWidget :
	public QWidget
{
public:
	QImageViewerWidget(QWidget  *parent =nullptr);
	~QImageViewerWidget();

	bool loadFile(const QString &);
	void setImage(const QImage &newImage);

private:
	void scaleImage(double factor);
	void adjustScrollBar(QScrollBar *scrollBar, double factor);

private:
	QLabel *_imageDisplay;
	QScrollArea *_scrollArea;
	double _scaleFactor;
	QImage _image;
};

