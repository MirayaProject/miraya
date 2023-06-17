#include "updater.h"

Updater::Updater(QObject *parent)
	: QObject{parent}
{
}

void Updater::checkVersion()
{
	qDebug() << "[Updater] starting version check";
	QNetworkAccessManager *manager = new QNetworkAccessManager(this);
	connect(manager, &QNetworkAccessManager::finished, this, &Updater::onReplyFinished);

	QUrl url("https://api.github.com/repos/MirayaProject/miraya/releases/latest");
	QNetworkRequest request(url);
	request.setHeader(QNetworkRequest::UserAgentHeader, "Miraya");
	manager->get(request);
	qDebug() << "[Updater] version check request sent";
}

void Updater::onReplyFinished(QNetworkReply *reply)
{
	qDebug() << "[Updater] version reply received";
	if (reply->error() != QNetworkReply::NoError){
		return;
	}

	QByteArray responseData = reply->readAll();
	QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
	QJsonObject jsonObj = jsonDoc.object();

	QString latestVersionStr = jsonObj.value("tag_name").toString();
	QVersionNumber latestVersion = QVersionNumber::fromString(latestVersionStr);
	QVersionNumber currentVersion = QVersionNumber::fromString(QCoreApplication::applicationVersion());

	if(currentVersion >= latestVersion){
		qDebug() << "[Updater] already running on latest or pre-release version";
		return;
	}
	emit newVersionAvailable();
}
