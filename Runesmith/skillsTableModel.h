#ifndef SKILLSTV_H
#define SKILLSTV_H

#include <QAbstractTableModel>
#include <DFHack.h>
#define DTM_COL_COUNT 4

class skillsTV : public QAbstractTableModel
{
	Q_OBJECT

public:
	skillsTV(QObject *parent = 0);
	~skillsTV(void);
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role) const;
	QVariant headerData(int section, Qt::Orientation orientation,
		int role = Qt::DisplayRole) const;
};

#endif