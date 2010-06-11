#ifndef PROGBARDELEGATE_H
#define PROGBARDELEGATE_H

#include <QStyledItemDelegate>
#include "DFInterface.h"

class progBarDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	progBarDelegate(QObject  *parent = 0);
	virtual ~progBarDelegate(void);
	void paint(QPainter * painter, const QStyleOptionViewItem  & option, const QModelIndex & index) const;
	void setDFI(DFInterface *nDFI);
	void setCreature(DFHack::t_creature *nCreature);

private:
	DFHack::t_creature *creature;
	DFInterface *DFI;
};

#endif