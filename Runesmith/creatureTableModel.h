#ifndef CREATURETABLEMODEL_H
#define CREATURETABLEMODEL_H

#include "dwarfTableModel.h"

class creatureTableModel : public dwarfTableModel
{
	Q_OBJECT

public:
	creatureTableModel(QObject *parent = 0);
	~creatureTableModel(void);
	QVariant data(const QModelIndex &index, int role) const;
	QVariant headerData(int section, Qt::Orientation orientation,
		int role = Qt::DisplayRole) const;

public slots:
	void update(const int &numCreatures);
};

#endif
