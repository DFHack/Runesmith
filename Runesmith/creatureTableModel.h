#ifndef CREATURETABLEMODEL_H
#define CREATURETABLEMODEL_H

#include "dwarfTableModel.h"

class creatureTableModel : public dwarfTableModel
{
	Q_OBJECT

public:
	creatureTableModel(QObject *parent = 0);
	virtual ~creatureTableModel(void);
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role) const;
	QVariant headerData(int section,
		Qt::Orientation orientation,
		int role = Qt::DisplayRole) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;
	bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
};

#endif
