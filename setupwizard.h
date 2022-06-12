#ifndef SETUPWIZARD_H
#define SETUPWIZARD_H

#include <QWizard>

namespace Ui {
  class SetupWizard;
}

class SetupWizard : public QWizard
{
  Q_OBJECT

public:
  explicit SetupWizard(QWidget *parent = nullptr);
  ~SetupWizard();

private slots:
  void on_SetupWizard_finished(int result);

private:
  Ui::SetupWizard *ui;
};

#endif // SETUPWIZARD_H
