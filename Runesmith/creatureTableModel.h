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
	Qt::ItemFlags flags(const QModelIndex &index) const;

	QVariant headerData(int section,
		Qt::Orientation orientation,
		int role = Qt::DisplayRole) const;

	bool setData(const QModelIndex &index,
		const QVariant &value,
		int role = Qt::EditRole);
	
	void setCurrent(RSCreature* nCreature);
	virtual void sort(int column, Qt::SortOrder order = Qt::AscendingOrder);

public slots:
	void genocide();

private:
	RSCreature* selectedCreature;
};

#endif
