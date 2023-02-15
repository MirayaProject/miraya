#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	this->setupUi();

	QSettings settings;
	twitchClient = new TwitchClient(this);
	gosumemoryClient = new GosumemoryClient(this);
	osuIrcClient = new OsuIrcClient(this);

	twitchCommandHandler = new TwitchCommandHandler();
	this->setupSignals();

	if(!settings.value("setup/completed").toBool()){
		on_actionStart_Setup_triggered();
	}
}


MainWindow::~MainWindow()
{
	delete twitchClient;
	delete gosumemoryClient;
	delete osuIrcClient;
	delete twitchCommandHandler;
	delete ui;
}


void MainWindow::setupUi()
{
	this->setupStatusbar();
	this->loadTheme();
}


void MainWindow::setupStatusbar()
{
	twitchConnectionLabel = new QLabel(this);
	gosumemoryConnectionLabel = new QLabel(this);
	ircConnectionLabel = new QLabel(this);

	ui->statusbar->addPermanentWidget(twitchConnectionLabel);
	ui->statusbar->addPermanentWidget(gosumemoryConnectionLabel);
	ui->statusbar->addPermanentWidget(ircConnectionLabel);
}


void MainWindow::loadTheme()
{
	QSettings settings;
	bool isDarkMode;
	auto darkModeSetting = settings.value("theme/darkMode");
	auto darkModeSettingExists = !darkModeSetting.isNull();

	if (darkModeSettingExists) {
		// If present, prefer local settings.
		loadThemeFromSetting(darkModeSetting);
	}
	else {
		#ifdef Q_OS_WIN
			loadDefaultThemeWindows();
		#endif
		loadLightMode();
	}
}


void MainWindow::loadThemeFromSetting(QVariant darkModeSetting)
{
	qDebug() << "[MainWindow] loading theme from settings";
	bool isDarkMode = darkModeSetting.toBool();
	if (isDarkMode) {
		loadDarkMode();
	}
	else {
		loadLightMode();
	}
}


void MainWindow::loadDefaultThemeWindows()
{
	qDebug() << "[MainWindow](Windows) loading system theme";

	// In windows>=10, you can set a default behaviour for app themes in the settings menu.
	// TODO: Check for major and minor version of windows.
	// Perhaps this can be used in linux and macos too?
	QSettings windowsSettings(
		"HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
		QSettings::NativeFormat
	);
	auto isDarkMode = windowsSettings.value("AppsUseLightTheme") == 0;

	if (isDarkMode) {
		loadDarkMode();
	}
}


void MainWindow::loadDarkMode()
{
	qDebug() << "[MainWindow] loading dark theme";
	qApp->setStyle(QStyleFactory::create("Fusion"));
	QPalette darkPalette;
	QColor darkColor = QColor(45,45,45);
	QColor disabledColor = QColor(127,127,127);

	darkPalette.setColor(QPalette::Window, darkColor);
	darkPalette.setColor(QPalette::WindowText, Qt::white);
	darkPalette.setColor(QPalette::Base, QColor(18,18,18));
	darkPalette.setColor(QPalette::AlternateBase, darkColor);
	darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
	darkPalette.setColor(QPalette::ToolTipText, Qt::white);
	darkPalette.setColor(QPalette::Text, Qt::white);
	darkPalette.setColor(QPalette::Disabled, QPalette::Text, disabledColor);
	darkPalette.setColor(QPalette::Button, darkColor);
	darkPalette.setColor(QPalette::ButtonText, Qt::white);
	darkPalette.setColor(QPalette::Disabled, QPalette::ButtonText, disabledColor);
	darkPalette.setColor(QPalette::BrightText, Qt::red);
	darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
	darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
	darkPalette.setColor(QPalette::HighlightedText, Qt::black);
	darkPalette.setColor(QPalette::Disabled, QPalette::HighlightedText, disabledColor);

	qApp->setPalette(darkPalette);
	qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");
}


void MainWindow::loadLightMode()
{
	QPalette lightPalette;
	qApp->setPalette(lightPalette);
	qApp->setStyleSheet("");
	qDebug() << "[MainWindow] loading light theme";
	// TODO: implement? Is it actually needed?
}


void MainWindow::setupSignals()
{
	connect(twitchClient, &TwitchClient::connected, this, &MainWindow::onTwitchClientConnected);
	connect(twitchClient, &TwitchClient::disconnected, this, &MainWindow::onTwitchClientDisconnected);
	connect(gosumemoryClient, &GosumemoryClient::connected, this, &MainWindow::onGosumemoryClientConnected);
	connect(gosumemoryClient, &GosumemoryClient::disconnected, this, &MainWindow::onGosumemoryClientDisconnected);
	connect(osuIrcClient, &OsuIrcClient::connected, this, &MainWindow::onOsuIrcClientConnected);
	connect(osuIrcClient, &OsuIrcClient::disconnected, this, &MainWindow::onOsuIrcClientDisconnected);

	connect(twitchClient, &TwitchClient::textMessageReceived, this, &MainWindow::onTwitchClientMessageReceived);
	connect(twitchClient, &TwitchClient::commandReceived, this, &MainWindow::onTwitchClientCommandReceived);
	connect(gosumemoryClient, &GosumemoryClient::messageReceived, this, &MainWindow::onGosumemoryClientMessageReceived);
}


void MainWindow::on_actionStart_Setup_triggered()
{
	SetupWizard(this).exec();
}


void MainWindow::on_actionGithub_triggered()
{
	QDesktopServices::openUrl(QUrl("https://www.github.com/MirayaProject/miraya"));
}


void MainWindow::on_actionDiscord_triggered()
{
	QDesktopServices::openUrl(QUrl("https://www.discord.gg/anHrS7p5Sf"));
}


void MainWindow::on_actionAbout_triggered()
{
	QMessageBox::about(this,
		"About Miraya",

		"<h1>Miraya</h1>"
		"<p>A Twitch chatbot with GosuMemory and osu! IRC support.</p>"
		"<p>Version: " + QApplication::applicationVersion() + "</p>"
		"<p>Copyright © 2022 Miraya Project</p>"
		"<p>This program is free software: you can redistribute it and/or modify "
		"it under the terms of the GNU General Public License as published by "
		"the Free Software Foundation, either version 3 of the License, or "
		"(at your option) any later version.</p>"
		"<p>This program is distributed in the hope that it will be useful, "
		"but WITHOUT ANY WARRANTY; without even the implied warranty of "
		"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the "
		"GNU General Public License for more details.</p>"
		"<p>You should have received a copy of the GNU General Public License "
		"along with this program.  If not, see <a href=\"https://www.gnu.org/licenses/\">"
		"https://www.gnu.org/licenses/</a>.</p>" +
		"<p>Icons provided by <a href=\"https://fonts.google.com/icons\">Google Fonts</a></p>"
	);
}


void MainWindow::on_actionPreferences_triggered()
{
	auto preferences = Preferences(this);
	connect(&preferences, &Preferences::themeChanged, this, &MainWindow::onThemeChanged);
	preferences.exec();
}


void MainWindow::on_actionSkins_triggered()
{
	SkinsUrl(gosumemoryClient, this).exec();
}


void MainWindow::on_btnStart_clicked()
{
	qDebug() << "[MainWindow] init";
	twitchClient->restart();
	gosumemoryClient->restart();
	osuIrcClient->restart();
}


void MainWindow::onThemeChanged()
{
	loadTheme();
}


void MainWindow::onGosumemoryClientMessageReceived(GosuMemoryDataWrapper message)
{
	// TODO: is this the best way to handle it? shouldn't it be &message?
	delete twitchCommandHandler->getGosumemoryData();
	twitchCommandHandler->setGosumemoryData(new GosuMemoryDataWrapper(message));
	QString title = message.getMapName();
	QString artist = message.getMapArtist();
	ui->nowPlayingLabel->setText(artist + " - " + title);
}


void MainWindow::onTwitchClientMessageReceived(TwitchDataWrapper message)
{
	// TODO: this should not be here
	for (auto val : Utils().getOsuBeatmapUrls(message.getMessage())) {
		qDebug() << "MainWindow: Osu beatmap url:" << val;
		osuIrcClient->sendMap(QUrl(val), message);
	}

	ui->twitchChat->addItem(getTwitchChatMessage(message.getUsername(), message.getMessage()));
	ui->twitchChat->scrollToBottom();
}


QListWidgetItem* MainWindow::getTwitchChatMessage(QString username, QString message)
{
	QListWidgetItem *item = new QListWidgetItem(username + ": " + message);
	item->setFlags(item->flags() & Qt::ItemIsEnabled);
	return item;
}


void MainWindow::onTwitchClientCommandReceived(TwitchDataWrapper command)
{
	twitchCommandHandler->setTwitchData(&command);
	QString response = twitchCommandHandler->getResponse();
	twitchClient->sendChatMessage(response);
}


void MainWindow::onOsuIrcClientConnected()
{
	ircConnectionLabel->setText("IRC ✔️");
}


void MainWindow::onTwitchClientConnected()
{
	twitchConnectionLabel->setText("Twitch ✔️");
}


void MainWindow::onGosumemoryClientConnected()
{
	gosumemoryConnectionLabel->setText("Gosumemory ✔️");
}


void MainWindow::onOsuIrcClientDisconnected()
{
	ircConnectionLabel->setText("IRC ❌");
}


void MainWindow::onTwitchClientDisconnected()
{
	twitchConnectionLabel->setText("Twitch ❌");
}


void MainWindow::onGosumemoryClientDisconnected()
{
	gosumemoryConnectionLabel->setText("Gosumemory ❌");
}
