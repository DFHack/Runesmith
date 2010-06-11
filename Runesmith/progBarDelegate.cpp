#include <QtGui>
#include <QStyle>
#include <QStringList>
#include "progBarDelegate.h"

progBarDelegate::progBarDelegate(QObject  *parent) 
: QStyledItemDelegate(parent), DFI(NULL), creature(NULL)
{
}

progBarDelegate::~progBarDelegate(void)
{
}

void progBarDelegate::paint(QPainter * painter, const QStyleOptionViewItem  & option, const QModelIndex & index) const
{	
	QStyleOptionProgressBar opt;
	DFHack::t_level levelinfo;

	if(!DFI || !creature)
	{
		opt.minimum = 0;
		opt.maximum = 0;
		opt.progress = 0;
		opt.text = QString("-");
	}
	else
	{		
		levelinfo = DFI->getLevelInfo(creature->defaultSoul.skills[index.row()].rating);
		opt.minimum = 0;
		opt.maximum = 100;
		opt.progress = (index.data().toInt()*100)/levelinfo.xpNxtLvl;
		opt.text = QString("%1%").arg(opt.progress);
	}

	opt.textVisible = true;
	opt.rect = option.rect;
	QApplication::style()->drawControl(QStyle::CE_ProgressBar, &opt, painter, (QWidget*)parent());
}

void progBarDelegate::setDFI(DFInterface *nDFI)
{
	DFI = nDFI;
}

void progBarDelegate::setCreature(DFHack::t_creature *nCreature)
{
	if(nCreature)
		creature = nCreature;
	else	
		creature = NULL;
}
