#ifndef SETUPWIZARD_H
#define SETUPWIZARD_H

#include <QWizard>
#include <QJsonObject>

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
  QJsonObject gatherData();
  Ui::SetupWizard *ui;
};

#endif // SETUPWIZARD_H
