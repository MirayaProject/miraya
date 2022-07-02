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
	connect(twitchClient, &TwitchClient::textMessageReceived, this, &MainWindow::on_twitchClient_messageReceived);
	connect(gosumemoryClient, &GosumemoryClient::messageReceived, this, &MainWindow::on_gosumemoryClient_messageReceived);
}


MainWindow::~MainWindow()
{
	delete ui;
}


void MainWindow::on_actionStart_Setup_triggered()
{
	connect(setupWizard, &SetupWizard::wizardFinished, this, &MainWindow::on_setupFinished);
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
}


void MainWindow::on_actionAbout_triggered()
{
	// TODO: DEBUG: move this
	qDebug() << "about";
	twitchClient->init();
	gosumemoryClient->init();
}


void MainWindow::on_gosumemoryClient_messageReceived(QString message)
{
	// TODO: remove this
	QJsonObject json = QJsonDocument::fromJson(message.toUtf8()).object();

	QString title = json["menu"].toObject()["bm"].toObject()["metadata"].toObject()["title"].toString();
	QString artist = json["menu"].toObject()["bm"].toObject()["metadata"].toObject()["artist"].toString();

	ui->nowPlayingLabel->setText(artist + " - " + title);
}

void MainWindow::on_twitchClient_messageReceived(TwitchDataWrapper message)
{
	ui->twitchChat->addItem(getTwitchChatMessage(message.getUsername(), message.getMessage()));
	ui->twitchChat->scrollToBottom();
}


QListWidgetItem* MainWindow::getTwitchChatMessage(QString username, QString message)
{
	QListWidgetItem *item = new QListWidgetItem(username + ": " + message);
	item->setFlags(item->flags() & Qt::ItemIsEnabled);
	return item;
}
