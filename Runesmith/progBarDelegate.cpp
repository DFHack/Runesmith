#include <QtGui>
#include <QStyle>
#include "progBarDelegate.h"

progBarDelegate::progBarDelegate(QObject  *parent) : QStyledItemDelegate(parent)
{
}

progBarDelegate::~progBarDelegate(void)
{
}

void progBarDelegate::paint(QPainter * painter, const QStyleOptionViewItem  & option, const QModelIndex & index) const
{	
	QStyleOptionProgressBar opt;
	opt.rect = option.rect;
	opt.minimum = 0;
	opt.maximum = ATTR_MAX;
	opt.progress = (index.data().toInt()*100)/ATTR_MAX;
	opt.text = QString("%1%").arg((index.data().toInt()*100)/ATTR_MAX);
	opt.textVisible = true;
	QApplication::style()->drawControl(QStyle::CE_ProgressBar, &opt, painter, (QWidget*)parent());
}
