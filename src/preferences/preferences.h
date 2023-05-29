#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QDialog>
#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QSettings>
#include <QTextStream>

namespace Ui {
  class Preferences;
}

class Preferences : public QDialog
{
  Q_OBJECT

public:
  explicit Preferences(QWidget *parent = nullptr);
  ~Preferences();

private:
  Ui::Preferences *ui;
  QSettings settings;
  void loadSettings();
  void loadTwitchSettings();
  void loadGosuMemorySettings();
  void loadOsuIrcSettings();
  void loadThemeSettings();
  void setupUi();
  void saveSettings();

  void on_saveBtnClicked();
  void on_backupBtn_clicked();
  void on_restoreBtn_clicked();
  void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

signals:
  void themeChanged();
};

#endif // PREFERENCES_H
