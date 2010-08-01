#ifndef FLAGTM_H
#define FLAGTM_H

#include <vector>
#include "skillsTableModel.h"
#define NUM_FLAGS_SHOWN 62

class flagTableModel : public skillsTableModel
{
	Q_OBJECT

public:
	flagTableModel(QObject *parent);
	virtual ~flagTableModel(void);
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;

	QVariant headerData(int section,
		Qt::Orientation orientation,
		int role = Qt::DisplayRole) const;
	
	bool setData(const QModelIndex &index, 
		const QVariant &value,
		int role = Qt::EditRole);
};

#endif
