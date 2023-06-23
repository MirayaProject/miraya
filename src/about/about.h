#ifndef ABOUT_H
#define ABOUT_H

#include <QApplication>
#include <QDate>
#include <QDebug>
#include <QMessageBox>
#include <QObject>

class About : public QObject
{
	Q_OBJECT
public:
	static void show();
};

#endif // ABOUT_H
