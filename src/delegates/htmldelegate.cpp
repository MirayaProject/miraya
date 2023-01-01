#include "htmldelegate.h"

HTMLDelegate::HTMLDelegate()
{

}

void HTMLDelegate::paint(QPainter *painter, QStyleOptionViewItem &option, QModelIndex &index)
{
	painter->save();
	auto options = QStyleOptionViewItem(option);
	initStyleOption(&options, index);
	doc.setHtml(options.text);
	options.text = "";

	QStyle *style = (options.widget == nullptr) ? QApplication::style() : options.widget->style();
	style->drawControl(QStyle::CE_ItemViewItem, &options, painter);

	auto ctx = QAbstractTextDocumentLayout::PaintContext();
	if (option.state & QStyle::State_Selected)
	{
		ctx.palette.setColor(QPalette::Text, option.palette.color(QPalette::Active, QPalette::HighlightedText));
	}
	else {
		ctx.palette.setColor(QPalette::Text, option.palette.color(QPalette::Active, QPalette::Text));
	}
	auto textRect = style->subElementRect(QStyle::SE_ItemViewItemText, &options);
	if (index.column() != 0) {
		textRect.adjust(5, 0, 0, 0);
	}
	int constant = 4;
	int margin = (option.rect.height() - options.fontMetrics.height()) / 2;
	margin = margin - constant;
	textRect.setTop(textRect.top() + margin);

	painter->translate(textRect.topLeft());
	painter->setClipRect(textRect.translated(- textRect.topLeft()));
	doc.documentLayout()->draw(painter, ctx);
	painter->restore();
}
