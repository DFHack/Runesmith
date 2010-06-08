#ifndef SKILLSTM_H
#define SKILLSTM_H

#include <QAbstractTableModel>
#include "DFInterface.h"
#define STM_COL_COUNT 3

class skillsTableModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	skillsTableModel(QObject *parent = 0);
	virtual ~skillsTableModel(void);
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role) const;
	QVariant headerData(int section,
		Qt::Orientation orientation,
		int role = Qt::DisplayRole) const;
	void setCreature(DFInterface *nDFI, const DFHack::t_creature *nCreature);
	void clear();

protected:
	const DFHack::t_creature *creature;
	DFInterface *DFI;
};

#endif