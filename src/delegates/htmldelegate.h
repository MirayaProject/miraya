#ifndef HTMLDELEGATE_H
#define HTMLDELEGATE_H

#include <QStyledItemDelegate>
#include <QAbstractTextDocumentLayout>
#include <QApplication>
#include <QWidget>
#include <QTextDocument>
#include <QPainter>
#include <QStyleOptionViewItem>
#include <QModelIndex>

// From https://stackoverflow.com/a/1956781
class HTMLDelegate : public QStyledItemDelegate
{
protected:
	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // HTMLDELEGATE_H
