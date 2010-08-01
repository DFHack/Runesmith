#ifndef LABTM_H
#define LABTM_H

#include <vector>
#include "skillsTableModel.h"

class labTableModel : public skillsTableModel
{
	Q_OBJECT

public:
	labTableModel(QObject *parent);
	virtual ~labTableModel(void);
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role) const;
	QVariant headerData(int section,
		Qt::Orientation orientation,
		int role = Qt::DisplayRole) const;
	void setCreature(RSCreature* nCreature);
};

#endif
