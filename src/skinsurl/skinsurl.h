#ifndef SKINSURL_H
#define SKINSURL_H

#include <QDialog>
#include <QMessageBox>
#include "osu/data/gosu/gosumemoryclient.h"
#include "osu/data/gosu/gosumemorydatawrapper.h"

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
  void on_removeSkinBtn_clicked();
  void on_gosumemoryMessage_received(GosuMemoryDataWrapper message);
  void on_saveBtnClicked();

  void loadData();
  void addRow(QString skinName, QString skinUrl = "");
  QStringList getListedSkins();
  QString getSkinName();
  bool isUrl(QString str);

  Ui::SkinsUrl *ui;
  GosumemoryClient *gosumemoryClient;
};

#endif // SKINSURL_H
