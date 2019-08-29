#include "QtRegex.h"

QtRegex::QtRegex(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.pushButton, &QPushButton::clicked, this, &QtRegex::onRegex);
}

void QtRegex::onRegex(bool)
{
	ui.regexResult->clear();

	if(ui.regex->text().isEmpty())
		return;

	if(ui.inputstring->toPlainText().isEmpty())
		return;

	QString regex = ui.regex->text();
	QRegExp rxlen(regex);
	QString regexInput = ui.inputstring->toPlainText();
	regexInput.simplified();

	int pos = 0;
	int i = 1;
	int strCount = regexInput.length();
	while((pos < strCount)&& (pos == rxlen.indexIn(regexInput, pos)) != -1) {
		QStringList capture = rxlen.capturedTexts();
		if(!capture.empty() && (!capture.at(0).isEmpty())) {
			QString var = "capture" + QString::number(i++) + " = " + capture.at(0);
			ui.regexResult->append(var);
		}

		if(rxlen.matchedLength() == 0 && pos < strCount)
			pos += 1;
		else
			pos += rxlen.matchedLength();
	}
	//int pos = rxlen.indexIn(regexInput);
	//
	//if(pos > -1) {
	//	int x = rxlen.matchedLength();
	//	QString firt = rxlen.cap(0);
	//	QStringList capture = rxlen.capturedTexts();
	//	for(int i = 0; i < capture.count(); i++) {
	//		ui.regexResult->append("capture" + QString::number(i) + " = " + capture.at(i));
	//	}
	//}
}
