#include "preferences.h"
#include "ui_preferences.h"

Preferences::Preferences(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Preferences)
{
  ui->setupUi(this);
  connect(ui->listWidget, &QListWidget::currentItemChanged, this, &Preferences::on_listWidget_currentItemChanged);
  ui->listWidget->setCurrentRow(0);
  loadSettings();
}

Preferences::~Preferences()
{
  delete ui;
}

void Preferences::loadSettings()
{
  loadGosuMemorySettings();
  loadTwitchSettings();
  loadOsuIrcSettings();
}


void Preferences::loadTwitchSettings()
{
  ui->twitchBotNickLineEdit->setText(settings.value("twitch/botNick").toString());
  ui->twitchBotOAuthLineEdit->setText(settings.value("twitch/oauth").toString());
  ui->twitchChannelLineEdit->setText(settings.value("twitch/channel").toString());
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


void Preferences::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
  if (current == nullptr)
    return;
  auto index = ui->listWidget->currentRow();
  ui->stackedWidget->setCurrentIndex(index);
}