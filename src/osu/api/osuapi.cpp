#include "osuapi.h"

OsuApi::OsuApi()
{
	qDebug() << "[OsuApi] Init";
	QSettings settings;
	clientId = settings.value("osuapi/clientId").toString();
	clientSecret = settings.value("osuapi/clientSecret").toString();
	oAuthUrl = "https://osu.ppy.sh/oauth/token";

	if (!(clientId.isEmpty() || clientSecret.isEmpty())) {
		token = ClientCredentialsFlow::getToken(clientId, clientSecret, oAuthUrl);
	}
	else {
		qDebug() << "[OsuApi] Client ID or Client Secret are empty";
	}
}

QJsonObject OsuApi::getBeatmapInfo(int beatmapId)
{
	// TODO: A lot can be split into smaller functions
	// TODO: also, the QEventLoop is making everything synchronous, which is suboptimal to say the least.
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

bool OsuApi::isValid()
{
	return !(clientId.isEmpty() || clientSecret.isEmpty());
}
