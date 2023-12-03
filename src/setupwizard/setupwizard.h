#ifndef SETUPWIZARD_H
#define SETUPWIZARD_H

#include <QWizard>
#include <QJsonObject>
#include <QIntValidator>
#include <QSettings>

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
	QJsonObject getOsuApiData();
	QJsonObject getTwitchData();
	QJsonObject getOsuircData();
	void saveData(QJsonObject data);
	Ui::SetupWizard *ui;
};

#endif // SETUPWIZARD_H
