#ifndef DWARFTABLEMODEL_H
#define DWARFTABLEMODEL_H

#include <QAbstractTableModel>
#include <vector>
#include <DFGlobal.h>
#include <DFTypes.h>
#include <DFHackAPI.h>
#include <modules/Creatures.h>

#define DTM_COL_COUNT 4

class dwarfTableModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	dwarfTableModel(DFHack::API &nDF, QObject *parent = 0);
	~dwarfTableModel(void);
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role) const;
	QVariant headerData(int section, Qt::Orientation orientation,
		int role = Qt::DisplayRole) const;
	void update(DFHack::Creatures &Creatures);

private:
	std::vector<DFHack::t_creature> creatures;
	DFHack::API &DF;
};

#endif
