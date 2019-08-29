#include <QApplication>
#include <QCommandLineParser>

#include "QtImageViewer.h"
#include "QImageViewerWidget.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QImageViewerWidget widget;

	//widget.setFixedWidth(550);
	//widget.setFixedHeight(550);
	widget.show();

	widget.loadFile("D:\\works\\project\\AiSprite\\testcase\\report.PNG");
	//widget.exec();

	return app.exec();

	QGuiApplication::setApplicationDisplayName(ImageViewer::tr("Image Viewer"));
	QCommandLineParser commandLineParser;
	commandLineParser.addHelpOption();
	commandLineParser.addPositionalArgument(ImageViewer::tr("[file]"), ImageViewer::tr("Image file to open."));
	commandLineParser.process(QCoreApplication::arguments());
	ImageViewer imageViewer;
	if(!commandLineParser.positionalArguments().isEmpty()
	        && !imageViewer.loadFile(commandLineParser.positionalArguments().front())) {
		return -1;
	}
	imageViewer.show();
	return app.exec();
}