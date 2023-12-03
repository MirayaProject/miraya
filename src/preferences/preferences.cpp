#include "preferences.h"
#include "ui_preferences.h"

Preferences::Preferences(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::Preferences)
{
	ui->setupUi(this);
	connect(ui->listWidget, &QListWidget::currentItemChanged, this, &Preferences::on_listWidget_currentItemChanged);
	connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &Preferences::on_saveBtnClicked);
	connect(ui->backupBtn, &QPushButton::clicked, this, &Preferences::on_backupBtn_clicked);
	connect(ui->restoreBtn, &QPushButton::clicked, this, &Preferences::on_restoreBtn_clicked);
	ui->listWidget->setCurrentRow(0);
	loadSettings();
	setupUi();
}


Preferences::~Preferences()
{
	delete ui;
}


void Preferences::setupUi()
{
	// TODO: this should be a standalone widget.
	auto *portValidator = new QIntValidator(0, 65535, this);
	ui->gosumemoryPortLineEdit->setValidator(portValidator);
	ui->osuIrcPortLineEdit->setValidator(portValidator);


	// TODO: this should be a standalone widget.
	QString IpRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
	QRegularExpression IpRegex("^" + IpRange + "\\." + IpRange + "\\." + IpRange + "\\." + IpRange + "$");
	QRegularExpressionValidator *IpValidator = new QRegularExpressionValidator(IpRegex, this);
	ui->gosumemoryIpLineEdit->setValidator(IpValidator);

	// TODO: this should be a standalone widget.
	QRegularExpression oauthRegex("^oauth:.{30}$");
	QRegularExpressionValidator *oauthValidator = new QRegularExpressionValidator(oauthRegex, this);
	ui->twitchBotOAuthLineEdit->setValidator(oauthValidator);
}


void Preferences::loadSettings()
{
	loadGosuMemorySettings();
	loadTwitchSettings();
	loadOsuIrcSettings();
	loadThemeSettings();
	loadOsuApiSettings();
}


void Preferences::loadTwitchSettings()
{
	ui->twitchBotNickLineEdit->setText(settings.value("twitch/botNick").toString());
	ui->twitchBotOAuthLineEdit->setText(settings.value("twitch/oauth").toString());
	ui->twitchChannelLineEdit->setText(settings.value("twitch/channel").toString());
}

void Preferences::loadOsuApiSettings()
{
	ui->osuapiClientIdLineEdit->setText(settings.value("osuapi/clientId").toString());
	ui->osuapiClientSecretLineEdit->setText(settings.value("osuapi/clientSecret").toString());
}

void Preferences::loadGosuMemorySettings()
{
	ui->gosumemoryIpLineEdit->setText(settings.value("gosumemory/ip").toString());
	ui->gosumemoryPortLineEdit->setText(settings.value("gosumemory/port").toString());
}


void Preferences::loadOsuIrcSettings()
{
	ui->osuIrcNicknameLineEdit->setText(settings.value("osuirc/nick").toString());
	ui->osuIrcPasswordLineEdit->setText(settings.value("osuirc/password").toString());
	ui->osuIrcServerLineEdit->setText(settings.value("osuirc/server").toString());
	ui->osuIrcPortLineEdit->setText(settings.value("osuirc/port").toString());
}


void Preferences::loadThemeSettings()
{
	auto darkModeSetting = settings.value("theme/darkMode");

	if(darkModeSetting.isNull()){
		ui->themesDefaultRadio->setChecked(true);
	}
	else {
		bool isDarkMode = darkModeSetting.toBool();
		ui->themesLightRadio->setChecked(!isDarkMode);
		ui->themesDarkRadio->setChecked(isDarkMode);
	}
}


void Preferences::on_saveBtnClicked()
{
	saveSettings();
	QMessageBox().information(this, "Saved", "Settings saved");
	emit themeChanged();
	accept();
}


void Preferences::saveSettings()
{
	settings.setValue("twitch/botNick", ui->twitchBotNickLineEdit->text().toLower());
	settings.setValue("twitch/oauth", ui->twitchBotOAuthLineEdit->text());
	settings.setValue("twitch/channel", ui->twitchChannelLineEdit->text().toLower());

	settings.setValue("gosumemory/ip", ui->gosumemoryIpLineEdit->text());
	settings.setValue("gosumemory/port", ui->gosumemoryPortLineEdit->text());

	settings.setValue("osuapi/clientId", ui->osuapiClientIdLineEdit->text());
	settings.setValue("osuapi/clientSecret", ui->osuapiClientSecretLineEdit->text());

	// Spaces need to be replaced by underscores.
	// https://osu.ppy.sh/wiki/en/Community/Internet_Relay_Chat#connection
	settings.setValue("osuirc/nick", ui->osuIrcNicknameLineEdit->text().replace(' ', '_'));
	settings.setValue("osuirc/password", ui->osuIrcPasswordLineEdit->text());
	settings.setValue("osuirc/server", ui->osuIrcServerLineEdit->text());
	settings.setValue("osuirc/port", ui->osuIrcPortLineEdit->text());

	if (ui->themesDefaultRadio->isChecked() && settings.contains("theme/darkMode")) {
		settings.remove("theme/darkMode");
	}
	else {
		settings.setValue("theme/darkMode", ui->themesDarkRadio->isChecked());
	}
}


void Preferences::on_backupBtn_clicked()
{
	QString message = QString("%1<br>%2").arg(
		"Would you like to include sensitive informations in your backup file?",
		"Anyone that has this information <b>will be able to access your accounts!</b>"
	);

	auto buttonAnswer = QMessageBox().question(
		this,
		"Sensitive information",
		message,
		QMessageBox::No | QMessageBox::Yes,
		QMessageBox::No
	);
	bool includeSensitiveInfo = buttonAnswer == QMessageBox::Yes;

	QString filePath = QFileDialog::getSaveFileName(nullptr, "Export Settings", QString(), "JSON Files (*.json)");
	Backup::backup(filePath, includeSensitiveInfo);
}


void Preferences::on_restoreBtn_clicked()
{
	QString filePath = QFileDialog::getOpenFileName(nullptr, "Import Settings", QString(), "JSON Files (*.json)");
	Backup::restore(filePath);
	// reloading
	loadSettings();
	QMessageBox().information(this, "Backup Restored", "Backup restored successfully");
}


void Preferences::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
	if (current == nullptr)
		return;
	auto index = ui->listWidget->currentRow();
	ui->stackedWidget->setCurrentIndex(index);
}
