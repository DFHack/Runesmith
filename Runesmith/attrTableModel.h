#ifndef ATTRTM_H
#define ATTRTM_H

#include "skillsTableModel.h"
#define NUM_ATTRS 18

class attrTableModel : public skillsTableModel
{
	Q_OBJECT

public:
	attrTableModel(QObject *parent);
	virtual ~attrTableModel(void);
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role) const;
	QVariant headerData(int section,
		Qt::Orientation orientation,
		int role = Qt::DisplayRole) const;
};

#endif
