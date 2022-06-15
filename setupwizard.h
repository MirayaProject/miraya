#ifndef SETUPWIZARD_H
#define SETUPWIZARD_H

#include <QWizard>
#include <QJsonObject>
#include <QIntValidator>

namespace Ui {
  class SetupWizard;
}

class SetupWizard : public QWizard
{
  Q_OBJECT

public:
  explicit SetupWizard(QWidget *parent = nullptr);
  ~SetupWizard();

signals:
  void wizardFinished(QJsonObject json);

private slots:
  void on_SetupWizard_finished(int result);

private:
  void setupUi();

  QJsonObject gatherData();
  QJsonObject getGosumemoryData();
  QJsonObject getTwitchData();
  QJsonObject getOsuircData();

  Ui::SetupWizard *ui;
};

#endif // SETUPWIZARD_H
