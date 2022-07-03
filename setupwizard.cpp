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

// TODO: add validator for IP address
void SetupWizard::setupUi()
{
	ui->gosumemoryPortLineEdit->setValidator(new QIntValidator(0, 65535, this));
	ui->osuircPortLineEdit->setValidator(new QIntValidator(0, 65535, this));
}

void SetupWizard::on_SetupWizard_finished(int result)
{
	if (result == 1) {
		QJsonObject data = gatherData();
		saveData(data);
		emit wizardFinished(data);
	}
	qDebug() << "done" << result;
}

QJsonObject SetupWizard::gatherData()
{
	QJsonObject data;

	data["gosumemory"] = getGosumemoryData();
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

QJsonObject SetupWizard::getTwitchData()
{
	QString twitchBotNick = ui->twitchBotNickLineEdit->text();
	QString twitchOauth = ui->twitchOauthLineEdit->text();
	QString twitchChannel = ui->twitchChannelLineEdit->text();

	QJsonObject twitchData = QJsonObject{
		{"botNick", twitchBotNick},
		{"oauth", twitchOauth},
		{"channel", twitchChannel}
	};

	return twitchData;
}

QJsonObject SetupWizard::getOsuircData()
{
	QString osuircNick = ui->osuircNickLineEdit->text();
	QString osuircPassword = ui->osuircPasswordLineEdit->text();
	QString osuircServer = ui->osuircServerLineEdit->text();
	int osuircPort = ui->osuircPortLineEdit->text().toInt();

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
	QJsonObject gosumemoryData = data["gosumemory"].toObject();
	QJsonObject twitchData = data["twitch"].toObject();
	QJsonObject osuircData = data["osuirc"].toObject();

	settings.setValue("gosumemory/ip", gosumemoryData["ip"].toString());
	settings.setValue("gosumemory/port", gosumemoryData["port"].toInt());

	settings.setValue("twitch/botNick", twitchData["botNick"].toString());
	settings.setValue("twitch/oauth", twitchData["oauth"].toString());
	settings.setValue("twitch/channel", twitchData["channel"].toString());

	settings.setValue("osuirc/nick", osuircData["nick"].toString());
	settings.setValue("osuirc/password", osuircData["password"].toString());
	settings.setValue("osuirc/server", osuircData["server"].toString());
	settings.setValue("osuirc/port", osuircData["port"].toInt());
}
