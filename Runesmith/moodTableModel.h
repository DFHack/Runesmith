#ifndef MOODTM_H
#define MOODTM_H

#include "skillsTableModel.h"

class moodTableModel : public skillsTableModel
{
	Q_OBJECT

public:
	moodTableModel(QObject *parent);
	virtual ~moodTableModel(void);
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;

	QVariant headerData(int section,
		Qt::Orientation orientation,
		int role = Qt::DisplayRole) const;

	bool setData(const QModelIndex &index, 
		const QVariant &value,
		int role = Qt::EditRole);

	void setCreature(RSCreature* nCreature);
};

#endif
