#ifndef TRAITSTM_H
#define TRAITSTM_H

#include "skillsTableModel.h"
#define NUM_TRAITS 30

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
	void setCreature(DFInterface *nDFI, DFHack::t_creature *nCreature);

private:
	std::vector<QString> traits;
};

#endif
