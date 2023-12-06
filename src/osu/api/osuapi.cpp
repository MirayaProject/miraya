#include "osuapi.h"

OsuApi::OsuApi()
{
	qDebug() << "[OsuApi] Init";
	QSettings settings;
	clientId = settings.value("osuapi/clientId").toString();
	clientSecret = settings.value("osuapi/clientSecret").toString();
	oAuthUrl = "https://osu.ppy.sh/oauth/token";
	token = ClientCredentialsFlow::getToken(clientId, clientSecret, oAuthUrl);
}

QJsonObject OsuApi::getBeatmapInfo(int beatmapId)
{
	// TODO: A lot can be split into smaller functions
	qDebug() << "[OsuApi] getBeatmapInfo";
	QNetworkAccessManager manager;
	QUrl url(QString("https://osu.ppy.sh/api/v2/beatmaps/%1").arg(beatmapId));

	QNetworkRequest request(url);

	QString accessToken = token["access_token"].toString();

	request.setRawHeader(
		QByteArray("Authorization"),
		(QString("Bearer %1").arg(accessToken)).toUtf8()
	);

	QNetworkReply *reply = manager.get(request);

	QEventLoop loop;
	QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
	loop.exec();

	qDebug() << "[OsuApi] get request done";
	int httpStatusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	qDebug() << "[OsuApi] HTTP Status code: " << httpStatusCode;
	if (httpStatusCode == 200) {
		QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
		QJsonObject obj = doc.object();
		qDebug() << "[OsuApi] Beatmap info: " << obj;
		return obj;
	}
	qDebug() << "[OsuApi] Error: " << reply->errorString();
	return QJsonObject();
}
