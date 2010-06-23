#ifndef SKILLSTM_H
#define SKILLSTM_H

#include <QAbstractTableModel>
#include "DFInterface.h"

class skillsTableModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	skillsTableModel(QObject *parent = 0, int nColCount = 3);
	virtual ~skillsTableModel(void);
	virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;
	virtual QVariant data(const QModelIndex &index, int role) const;
	virtual QVariant headerData(int section,
		Qt::Orientation orientation,
		int role = Qt::DisplayRole) const;
	virtual void setCreature(DFInterface *nDFI, DFHack::t_creature *nCreature);
	void clear();
	int getNumCols();
	virtual Qt::ItemFlags flags(const QModelIndex &index) const;
	virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
	
protected:
	DFHack::t_creature *creature;
	DFInterface *DFI;
	const int colCount;
};

#endif