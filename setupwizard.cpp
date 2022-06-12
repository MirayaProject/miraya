#include "setupwizard.h"
#include "ui_setupwizard.h"

SetupWizard::SetupWizard(QWidget *parent) :
  QWizard(parent),
  ui(new Ui::SetupWizard)
{
  ui->setupUi(this);
}

SetupWizard::~SetupWizard()
{
  delete ui;
}

void SetupWizard::on_SetupWizard_finished(int result)
{
    qDebug() << "done" << result;
}

