#include "setupwizard.h"
#include "ui_setupwizard.h"

SetupWizard::SetupWizard(QWidget *parent) :
	QWizard(parent),
	ui(new Ui::SetupWizard)
{
	ui->setupUi(this);
}

SetupWizard::~SetupWizard()
{
	delete ui;
}

void SetupWizard::on_SetupWizard_finished(int result)
{
	if (result == 1) {
		QJsonObject data = gatherData();
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