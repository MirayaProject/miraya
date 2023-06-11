#ifndef ABOUT_H
#define ABOUT_H

#include <QApplication>
#include <QDebug>
#include <QMessageBox>
#include <QObject>

class About : public QObject
{
	Q_OBJECT
public:
	explicit About(QObject *parent = nullptr);
	static void show();
};

#endif // ABOUT_H
