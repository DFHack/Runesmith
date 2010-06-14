#ifndef MISCTM_H
#define MISCTM_H

#include "skillsTableModel.h"

class miscTableModel : public skillsTableModel
{
	Q_OBJECT

public:
	miscTableModel(QObject *parent);
	virtual ~miscTableModel(void);
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role) const;
	QVariant headerData(int section,
		Qt::Orientation orientation,
		int role = Qt::DisplayRole) const;

private:
	QString calcDob() const;
};

#endif
