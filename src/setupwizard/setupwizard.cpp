#include "setupwizard.h"
#include "ui_setupwizard.h"

SetupWizard::SetupWizard(QWidget *parent) :
	QWizard(parent),
	ui(new Ui::SetupWizard)
{
	ui->setupUi(this);
	setupUi();
}

SetupWizard::~SetupWizard()
{
	delete ui;
}


void SetupWizard::setupUi()
{
	// TODO: this should be a standalone widget.
	auto *portValidator = new QIntValidator(0, 65535, this);
	ui->gosumemoryPortLineEdit->setValidator(portValidator);
	ui->osuircPortLineEdit->setValidator(portValidator);

	// TODO: this should be a standalone widget.
	QString IpRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
	QRegularExpression IpRegex("^" + IpRange + "\\." + IpRange + "\\." + IpRange + "\\." + IpRange + "$");
	QRegularExpressionValidator *IpValidator = new QRegularExpressionValidator(IpRegex, this);
	ui->gosumemoryIpLineEdit->setValidator(IpValidator);

	// TODO: this should be a standalone widget.
	QRegularExpression oauthRegex("^oauth:.{30}$");
	QRegularExpressionValidator *oauthValidator = new QRegularExpressionValidator(oauthRegex, this);
	ui->twitchOauthLineEdit->setValidator(oauthValidator);

	ui->gosumemoryExplanationLabel->setOpenExternalLinks(true);
	ui->twitchExplanationLabel->setOpenExternalLinks(true);
	ui->osuircExplanationLabel->setOpenExternalLinks(true);
}


void SetupWizard::on_SetupWizard_finished(int result)
{
	if (result == 1) {
		QJsonObject data = gatherData();
		saveData(data);
		emit wizardFinished(data);
	}
	qDebug() << "[SetupWizard] finished" << result;
}


QJsonObject SetupWizard::gatherData()
{
	QJsonObject data;
	data["gosumemory"] = getGosumemoryData();
	data["osuapi"] = getOsuApiData();
	data["twitch"] = getTwitchData();
	data["osuirc"] = getOsuircData();

	return data;
}


QJsonObject SetupWizard::getGosumemoryData()
{
	QString gosuIp = ui->gosumemoryIpLineEdit->text();
	int gosuPort = ui->gosumemoryPortLineEdit->text().toInt();

	QJsonObject gosumemoryData = QJsonObject{
		{"ip", gosuIp},
		{"port", gosuPort}
	};

	return gosumemoryData;
}

QJsonObject SetupWizard::getOsuApiData()
{
	int osuapiClientId = ui->osuapiClientIdLineEdit->text().toInt();
	QString osuapiClientSecret = ui->osuapiClientSecretLineEdit->text();

	QJsonObject osuapiClientData = QJsonObject{
		{"clientId", osuapiClientId},
		{"clientSecret", osuapiClientSecret}
	};

	return osuapiClientData;
}

QJsonObject SetupWizard::getTwitchData()
{
	QString twitchBotNick = ui->twitchBotNickLineEdit->text();
	QString twitchOauth = ui->twitchOauthLineEdit->text();
	QString twitchChannel = ui->twitchChannelLineEdit->text();

	QJsonObject twitchData = QJsonObject{
		{"botNick", twitchBotNick.toLower()},
		{"oauth", twitchOauth},
		{"channel", twitchChannel.toLower()}
	};

	return twitchData;
}


QJsonObject SetupWizard::getOsuircData()
{
	QString osuircNick = ui->osuircNickLineEdit->text();
	QString osuircPassword = ui->osuircPasswordLineEdit->text();
	QString osuircServer = ui->osuircServerLineEdit->text();
	int osuircPort = ui->osuircPortLineEdit->text().toInt();

	// Spaces need to be replaced by underscores.
	// https://osu.ppy.sh/wiki/en/Community/Internet_Relay_Chat#connection
	osuircNick.replace(' ', '_');

	QJsonObject osuircData = QJsonObject{
		{"nick", osuircNick},
		{"password", osuircPassword},
		{"server", osuircServer},
		{"port", osuircPort}
	};

	return osuircData;
}


void SetupWizard::saveData(QJsonObject data)
{
  QSettings settings;
	QJsonObject osuapiData = data["osuapi"].toObject();
	QJsonObject gosumemoryData = data["gosumemory"].toObject();
	QJsonObject twitchData = data["twitch"].toObject();
	QJsonObject osuircData = data["osuirc"].toObject();

	settings.setValue("gosumemory/ip", gosumemoryData["ip"].toString());
	settings.setValue("gosumemory/port", gosumemoryData["port"].toInt());

	settings.setValue("osuapi/clientId", osuapiData["clientId"].toInt());
	settings.setValue("osuapi/clientSecret", osuapiData["clientSecret"].toString());

	settings.setValue("twitch/botNick", twitchData["botNick"].toString());
	settings.setValue("twitch/oauth", twitchData["oauth"].toString());
	settings.setValue("twitch/channel", twitchData["channel"].toString());

	settings.setValue("osuirc/nick", osuircData["nick"].toString());
	settings.setValue("osuirc/password", osuircData["password"].toString());
	settings.setValue("osuirc/server", osuircData["server"].toString());
	settings.setValue("osuirc/port", osuircData["port"].toInt());

	settings.setValue("setup/completed", true);
}
