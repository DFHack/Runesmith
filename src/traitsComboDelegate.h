#ifndef TRAITSCOMBODELEGATE_H
#define TRAITSCOMBODELEGATE_H

 #include <QItemDelegate>
 #include <QModelIndex>
 #include <QObject>
 #include <QSize>
 #include <QComboBox>
#include "DFInterface.h"

class traitsComboDelegate : public QItemDelegate
{
	Q_OBJECT

public:
	traitsComboDelegate(QObject *parent = 0);
	~traitsComboDelegate(void);
	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;

	void setEditorData(QWidget *editor, const QModelIndex &index) const;
	void setModelData(QWidget *editor, QAbstractItemModel *model,
		const QModelIndex &index) const;
	void updateEditorGeometry(QWidget *editor,
		const QStyleOptionViewItem &option, const QModelIndex &index) const;
	void setDFI(DFInterface *nDFI);

private:
	DFInterface *DFI;
};

#endif