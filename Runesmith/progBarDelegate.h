#ifndef PROGBARDELEGATE_H
#define PROGBARDELEGATE_H

#include <QStyledItemDelegate>
#define ATTR_MAX 5000

class progBarDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	progBarDelegate(QObject  *parent = 0);
	~progBarDelegate(void);
	void paint(QPainter * painter, const QStyleOptionViewItem  & option, const QModelIndex & index) const;
};

#endif