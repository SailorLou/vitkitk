#include "ImageGraphicsWindow.h"
#include <QPushButton>
#include<QLabel>
#include <QFile>
#include <QDebug>
#include <QFileInfo>
#include <QDir>

#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork>
#include <QHttpMultiPart>

#include <QJsonObject>
#include <QJsonDocument>
#include <QSharedPointer>
#include <utility>
ImageGraphicsWindow::ImageGraphicsWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowTitle("base");

	//connect(ui.pushButton_3, &QPushButton::pressed, this, &ImageGraphicsWindow::onButtonClick);

	QLabel *xx = new QLabel(ui.widget);
	QSize size = ui.widget->size();

	xx->setStyleSheet("color:red;font-size:20px;font-family:Microsoft YaHei");
	xx->resize(size);
	//xx->adjustSize();
	xx->setAlignment(Qt::AlignCenter);

	xx->setText(QStringLiteral("当前序列被标为阳性"));

	ui.checkBox->setChecked(true);
	ui.checkBox->setDisabled(true);
}

void ImageGraphicsWindow::buildConnect()
{
	connect(ui.pushButton_3, &QPushButton::clicked, this, &ImageGraphicsWindow::onButtonClick);


	QString ur("http://bzsite.dev.proxima-ai.com/aaa/v1/anno/series_result/search");
	QUrl url(ur);

	QJsonObject json;
	QString id("1.2.826.0.1.3680043.2.461.20101127174049.206483.201011270192-0");
	json.insert("id", 943);
	json.insert("serialNumber", id);
	json.insert("type", "TASK");
	json.insert("userId", 5175);

	QJsonDocument document;
	document.setObject(json);

	QNetworkRequest request(url);
	request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));

	QString mima("343612c46dc24feb863a9fb52052ad1a_5175");
	request.setRawHeader("accessToken", mima.toLocal8Bit());

	auto pManager = new QNetworkAccessManager();
	QObject::connect(pManager, &QNetworkAccessManager::finished, this, [=](QNetworkReply *reply) {
		bool resFlag = false;
		QByteArray answer = reply->readAll();
		QJsonObject responseJson = QJsonDocument::fromJson(answer).object();

		int code = responseJson.value("code").toInt();
		if(!reply->error()) {

			if(code == 0) {
				QJsonObject dataJson = responseJson.value("data").toObject();
				QJsonDocument document2 = QJsonDocument(dataJson);
				QByteArray array = document2.toJson();
				printf("review series:%s\n", array.constData());
				//
				QJsonObject de = dataJson.value("list").toObject();
				QJsonDocument document1 = QJsonDocument(de);
				QByteArray arrays = document1.toJson();
				printf("review list:%s\n", arrays.constData());

				resFlag = true;
			}
		}
	});

	pManager->post(request, document.toJson(QJsonDocument::Compact));


}

void ImageGraphicsWindow::onButtonClick()
{
	ui.pushButton_3->setText("baseclass");
}
