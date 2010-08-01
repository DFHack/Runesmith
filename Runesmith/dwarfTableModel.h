#ifndef DWARFTABLEMODEL_H
#define DWARFTABLEMODEL_H

#include <QAbstractTableModel>
#include "DFInterface.h"
#include "RSCreature.h"
#define HAPPINESS_WEIGHT 30

class dwarfTableModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	dwarfTableModel(QObject *parent = 0, int nColCount = 4);
	~dwarfTableModel(void);
	virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;
	virtual QVariant data(const QModelIndex &index, int role) const;
	virtual QVariant headerData(int section,
		Qt::Orientation orientation,
		int role = Qt::DisplayRole) const;
	void update(DFInterface *nDFI);
	virtual Qt::ItemFlags flags(const QModelIndex &index) const;
	virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
	virtual void sort(int column, Qt::SortOrder order = Qt::AscendingOrder);

protected:
	DFInterface *DFI;
	const int colCount;
};

#endif
