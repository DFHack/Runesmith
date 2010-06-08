#ifndef SKILLSTV_H
#define SKILLSTV_H

#include <QAbstractTableModel>
#include <DFHack.h>
#define STM_COL_COUNT 2

class skillsTableModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	skillsTableModel(QObject *parent = 0);
	~skillsTableModel(void);
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role) const;
	QVariant headerData(int section,
		Qt::Orientation orientation,
		int role = Qt::DisplayRole) const;
	void setCreature(DFHack::Context *DF, const DFHack::t_creature *nCreature);

private:
	const DFHack::t_creature *creature;
	DFHack::memory_info *mem;
};

#endif