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


// Porting of https://stackoverflow.com/a/53572278/9950484
class HTMLDelegate : public QStyledItemDelegate
{
  Q_OBJECT

public:
  HTMLDelegate();
  void paint(QPainter *painter, QStyleOptionViewItem &option, QModelIndex &index);

private:
  QTextDocument doc;
};

#endif // HTMLDELEGATE_H
