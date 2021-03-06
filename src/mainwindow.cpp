#include <QDesktopServices>
#include <QUrl>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	setupWizard = new SetupWizard(this);

	QSettings settings;
	twitchClient = new TwitchClient(
		QUrl("ws://irc-ws.chat.twitch.tv:80"),
		settings.value("twitch/botNick").toString(),
		settings.value("twitch/oauth").toString(),
		settings.value("twitch/channel").toString(),
		this
	);

	gosumemoryClient = new GosumemoryClient(
		QUrl(
			"ws://"
			+ settings.value("gosumemory/ip").toString()
			+ ":"
			+ settings.value("gosumemory/port").toString()
			+ "/ws"
		),
		this
	);

	osuIrcClient = new OsuIrcClient(
		settings.value("osuirc/nick").toString(),
		settings.value("osuirc/password").toString(),
		settings.value("osuirc/server").toString(),
		settings.value("osuirc/port").toInt(),
		this
	);

	twitchCommandHandler = new TwitchCommandHandler();

	twitchConnectionLabel = new QLabel(this);
	gosumemoryConnectionLabel = new QLabel(this);
	ircConnectionLabel = new QLabel(this);

	ui->statusbar->addPermanentWidget(twitchConnectionLabel);
	ui->statusbar->addPermanentWidget(gosumemoryConnectionLabel);
	ui->statusbar->addPermanentWidget(ircConnectionLabel);

	connect(twitchClient, &TwitchClient::connected, this, &MainWindow::on_twitchClient_connected);
	connect(twitchClient, &TwitchClient::disconnected, this, &MainWindow::on_twitchClient_disconnected);
	connect(gosumemoryClient, &GosumemoryClient::connected, this, &MainWindow::on_gosumemoryClient_connected);
	connect(gosumemoryClient, &GosumemoryClient::disconnected, this, &MainWindow::on_gosumemoryClient_disconnected);
	connect(osuIrcClient, &OsuIrcClient::connected, this, &MainWindow::on_osuIrcClient_connected);
	connect(osuIrcClient, &OsuIrcClient::disconnected, this, &MainWindow::on_osuIrcClient_disconnected);

	connect(setupWizard, &SetupWizard::wizardFinished, this, &MainWindow::on_setupFinished);
	connect(twitchClient, &TwitchClient::textMessageReceived, this, &MainWindow::on_twitchClient_messageReceived);
	connect(twitchClient, &TwitchClient::commandReceived, this, &MainWindow::on_twitchClient_commandReceived);
	connect(gosumemoryClient, &GosumemoryClient::messageReceived, this, &MainWindow::on_gosumemoryClient_messageReceived);

	connect(ui->btnStart, &QPushButton::released, this, &MainWindow::on_init);
}


MainWindow::~MainWindow()
{
	delete ui;
}


void MainWindow::on_actionStart_Setup_triggered()
{
	setupWizard->restart();
	setupWizard->show();
}


void MainWindow::on_actionGithub_triggered()
{
	QDesktopServices::openUrl(QUrl("https://www.github.com/MirayaProject/miraya"));
}


void MainWindow::on_actionDiscord_triggered()
{
	QDesktopServices::openUrl(QUrl("https://www.discord.gg/anHrS7p5Sf"));
}


void MainWindow::on_setupFinished(QJsonObject data)
{
	qDebug() << "MainWindow: Setup finished with data:" << data;
	QSettings settings;
	twitchClient->setChannel(settings.value("twitch/channel").toString());
	twitchClient->setBotNick(settings.value("twitch/botNick").toString());
	twitchClient->setOauth(settings.value("twitch/oauth").toString());

	gosumemoryClient->setUrl(
		QUrl("ws://"
			+settings.value("gosumemory/ip").toString()
			+":"
			+settings.value("gosumemory/port").toString()
		)
	);
	osuIrcClient->setNick(settings.value("osuirc/nick").toString());
	osuIrcClient->setPassword(settings.value("osuirc/password").toString());
	osuIrcClient->setServer(settings.value("osuirc/server").toString());
	osuIrcClient->setPort(settings.value("osuirc/port").toInt());
}


void MainWindow::on_actionAbout_triggered()
{
	QMessageBox::about(this,
		"About Miraya",

		"<h1>Miraya</h1>"
		"<p>A Twitch chatbot with GosuMemory and osu! IRC support.</p>"
		"<p>Version: " + QApplication::applicationVersion() + "</p>"
		"<p>Copyright ?? 2022 Miraya Project</p>"
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
		"https://www.gnu.org/licenses/</a>.</p>"
	);
}


void MainWindow::on_init()
{
	qDebug() << "init";
	twitchClient->restart();
	gosumemoryClient->restart();
	osuIrcClient->restart();
}


void MainWindow::on_gosumemoryClient_messageReceived(GosuMemoryDataWrapper message)
{
	// TODO: is this the best way to handle it? shouldn't it be &message?
	delete twitchCommandHandler->getGosumemoryData();
	twitchCommandHandler->setGosumemoryData(new GosuMemoryDataWrapper(message));
	QString title = message.getMapName();
	QString artist = message.getMapArtist();
	ui->nowPlayingLabel->setText(artist + " - " + title);
}


void MainWindow::on_twitchClient_messageReceived(TwitchDataWrapper message)
{
	// TODO: this should not be here
	for (auto val : Utils().getOsuBeatmapUrls(message.getMessage())){
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


void MainWindow::on_twitchClient_commandReceived(TwitchDataWrapper command)
{
	twitchCommandHandler->setTwitchData(&command);
	QString response = twitchCommandHandler->getResponse();
	twitchClient->sendChatMessage(response);
}


void MainWindow::on_osuIrcClient_connected()
{
	ircConnectionLabel->setText("IRC ??????");
}


void MainWindow::on_twitchClient_connected()
{
	twitchConnectionLabel->setText("Twitch ??????");
}


void MainWindow::on_gosumemoryClient_connected()
{
	gosumemoryConnectionLabel->setText("Gosumemory ??????");
}



void MainWindow::on_osuIrcClient_disconnected()
{
	ircConnectionLabel->setText("IRC ???");
}


void MainWindow::on_twitchClient_disconnected()
{
	twitchConnectionLabel->setText("Twitch ???");
}


void MainWindow::on_gosumemoryClient_disconnected()
{
	gosumemoryConnectionLabel->setText("Gosumemory ???");
}
