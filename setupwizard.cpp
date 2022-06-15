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

void SetupWizard::on_SetupWizard_finished(int result) {
	if (result == 1) {
		QString gosuIp = ui->gosumemoryIpLineEdit->text();
		int gosuPort = ui->gosumemoryPortLineEdit->text().toInt();

		QString twitchChannel = ui->twitchChannelLineEdit->text();
		QString twitchBotNick = ui->twitchBotNickLineEdit->text();
		QString twitchOauth = ui->twitchOauthLineEdit->text();

		QString osuircServer = ui->osuircServerLineEdit->text();
		int osuircPort = ui->osuircPortLineEdit->text().toInt();
		QString osuircNick = ui->osuircNickLineEdit->text();
		QString osuircPassword = ui->osuircPasswordLineEdit->text();

		qDebug() << "gosu" << gosuIp << gosuPort;
		qDebug() << "twitch" << twitchBotNick << twitchChannel << twitchOauth;
		qDebug() << "osuirc" << osuircNick << osuircServer << osuircPort << osuircPassword;
	}
	qDebug() << "done" << result;
}
