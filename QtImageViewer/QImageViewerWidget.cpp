#include "QImageViewerWidget.h"

#include <qglobal.h>
#include <QLabel>
#include <QScrollArea>
#include <QImageReader>
#include <QScrollBar>
#include<QGridLayout>


QImageViewerWidget::QImageViewerWidget(QWidget  *parent) :QWidget(parent), _imageDisplay(new QLabel),
	_scrollArea(new QScrollArea), _scaleFactor(1), _image()
{

	_imageDisplay->setBackgroundRole(QPalette::Base);
	_imageDisplay->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	_imageDisplay->setScaledContents(true);

	_scrollArea->setBackgroundRole(QPalette::Dark);
	_scrollArea->setWidget(_imageDisplay);
	_scrollArea->setVisible(false);
	_scrollArea->setAlignment(Qt::AlignCenter);
	_scrollArea->setFrameShape(QFrame::NoFrame);

	QGridLayout *mainLayout = new QGridLayout(this);
	mainLayout->addWidget(_scrollArea, 0, 0);
	mainLayout->setMargin(0);


	setLayout(mainLayout);

	setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
	//showNormal();
}




QImageViewerWidget::~QImageViewerWidget()
{
}

bool QImageViewerWidget::loadFile(const QString &fileName)
{
	QImageReader reader(fileName);
	reader.setAutoTransform(true);
	const QImage newImage = reader.read();
	if(newImage.isNull()) {
		return false;
	}

	setImage(newImage);
}
void QImageViewerWidget::setImage(const QImage &newImage)
{
	_image = newImage;
	_imageDisplay->setPixmap(QPixmap::fromImage(_image));

	_scaleFactor = 1.0;

	_scrollArea->setVisible(true);
	_imageDisplay->resize(_image.size());
	_imageDisplay->adjustSize();
}
void QImageViewerWidget::scaleImage(double factor)
{
	Q_ASSERT(_imageDisplay->pixmap());
	_scaleFactor *= factor;
	_imageDisplay->resize(_scaleFactor * _imageDisplay->pixmap()->size());

	adjustScrollBar(_scrollArea->horizontalScrollBar(), factor);
	adjustScrollBar(_scrollArea->verticalScrollBar(), factor);
}

void QImageViewerWidget::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
	scrollBar->setValue(int(factor * scrollBar->value()
	                        + ((factor - 1) * scrollBar->pageStep() / 2)));
}
