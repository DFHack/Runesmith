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
	opt.progress = (index.data().toFloat()/ATTR_MAX)*100;
	opt.text = QString("%1%").arg((index.data().toFloat()/ATTR_MAX)*100);
	opt.textVisible = true;
	QApplication::style()->drawControl(QStyle::CE_ProgressBar, &opt, painter, (QWidget*)parent());
}
