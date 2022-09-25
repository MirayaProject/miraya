#ifndef SKINSURL_H
#define SKINSURL_H

#include <QDialog>
#include "gosumemoryClient.h"
#include "gosumemorydatawrapper.h"

namespace Ui {
  class SkinsUrl;
}

class SkinsUrl : public QDialog
{
  Q_OBJECT

public:
  explicit SkinsUrl(GosumemoryClient *client, QWidget *parent = nullptr);
  ~SkinsUrl();

private:
  void on_addSkinBtn_clicked();
  void on_gosumemoryMessage_received(GosuMemoryDataWrapper message);
  Ui::SkinsUrl *ui;
  GosumemoryClient *gosumemoryClient;
};

#endif // SKINSURL_H
