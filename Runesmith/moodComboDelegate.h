#ifndef MOODCOMBODELEGATE_H
#define MOODCOMBODELEGATE_H

#include <QItemDelegate>
#include <QModelIndex>
#include <QObject>
#include <QSize>
#include <QComboBox>
#include "DFInterface.h"

class moodComboDelegate : public QItemDelegate
{
	Q_OBJECT

public:
	moodComboDelegate(QObject *parent = 0);
	~moodComboDelegate(void);
	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;

	void setEditorData(QWidget *editor, const QModelIndex &index) const;
	void setModelData(QWidget *editor, QAbstractItemModel *model,
		const QModelIndex &index) const;
	void updateEditorGeometry(QWidget *editor,
		const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif