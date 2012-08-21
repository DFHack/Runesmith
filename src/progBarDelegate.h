#ifndef PROGBARDELEGATE_H
#define PROGBARDELEGATE_H

#include <QStyledItemDelegate>
#include "DFInterface.h"
#include "RSCreature.h"

class progBarDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	progBarDelegate(QObject  *parent = 0);
	virtual ~progBarDelegate(void);
	void paint(QPainter * painter, const QStyleOptionViewItem  & option, const QModelIndex & index) const;
	void updateEditorGeometry(QWidget *editor,
         const QStyleOptionViewItem &option, const QModelIndex &index) const;
	void setDFI(DFInterface *nDFI);
	void setCreature(RSCreature* nCreature);

private:
	RSCreature* creature;
	DFInterface *DFI;
};

#endif