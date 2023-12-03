#include "clientCredentialsFlow.h"

QJsonObject ClientCredentialsFlow::getToken(QString clientId, QString clientSecret, QString oAuthUrl)
{
	qDebug() << "[ClientCredentialsFlow] getToken";
	QNetworkAccessManager manager;
	QNetworkRequest request((QUrl(oAuthUrl)));

	request.setHeader(
		QNetworkRequest::ContentTypeHeader,
		"application/x-www-form-urlencoded"
	);
	request.setHeader(
		QNetworkRequest::UserAgentHeader,
		"Miraya"
	);

	QUrlQuery params;
	params.addQueryItem("client_id", clientId);
	params.addQueryItem("client_secret", clientSecret);
	params.addQueryItem("grant_type", "client_credentials");
	params.addQueryItem("scope", "public");

	QNetworkReply *reply = manager.post(request, params.toString(QUrl::FullyEncoded).toUtf8());

	QEventLoop loop;
	QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
	loop.exec();

	int httpStatusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

	qDebug() << "[ClientCredentialsFlow] HTTP Status code: " << httpStatusCode;
	if (httpStatusCode == 200) {
		QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
		QJsonObject obj = doc.object();
		return obj;
	}
	qDebug() << "[ClientCredentialsFlow] Failed to get token";
	QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
	qDebug() << QString(doc.toJson(QJsonDocument::Compact));
	return doc.object();
}
