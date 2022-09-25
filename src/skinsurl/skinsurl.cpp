#include "skinsurl.h"
#include "ui_skinsurl.h"

SkinsUrl::SkinsUrl(GosumemoryClient *client, QWidget *parent) :
  QDialog(parent)
  , gosumemoryClient(client)
  , ui(new Ui::SkinsUrl)
{
  ui->setupUi(this);
  connect(ui->addSkinBtn, &QPushButton::clicked, this, &SkinsUrl::on_addSkinBtn_clicked);
  connect(gosumemoryClient, &GosumemoryClient::messageReceived, this, &SkinsUrl::on_gosumemoryMessage_received);
}


SkinsUrl::~SkinsUrl()
{
  delete ui;
}


void SkinsUrl::on_addSkinBtn_clicked()
{
  ui->skinURLsTable->insertRow(ui->skinURLsTable->rowCount());
}


void SkinsUrl::on_gosumemoryMessage_received(GosuMemoryDataWrapper message)
{
  ui->currentSkinLabel->setText(message.getSkinName());
}
