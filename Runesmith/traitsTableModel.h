#ifndef TRAITSTM_H
#define TRAITSTM_H

#include <map>
#include "skillsTableModel.h"
#define NUM_TRAITS 30

struct TraitIndexItem
{
	QString text;
	unsigned int index;
};

class traitsTableModel : public skillsTableModel
{
	Q_OBJECT

public:
	traitsTableModel(QObject *parent);
	virtual ~traitsTableModel(void);
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role) const;
	QVariant headerData(int section,
		Qt::Orientation orientation,
		int role = Qt::DisplayRole) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;
	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);
	void setCreature(RSCreature* nCreature);
	RSCreature* getCreature();
	unsigned int getTraitIndex(unsigned int id);
	bool addTrait(int index1, int index2);
};

#endif
