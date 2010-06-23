#ifndef ATTRTM_H
#define ATTRTM_H

#include "skillsTableModel.h"
#define NUM_ATTRS 19

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
	bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
};

#endif
