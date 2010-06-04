#ifndef DWARFTABLEMODEL_H
#define DWARFTABLEMODEL_H

#include <QAbstractTableModel>
#include <vector>
#include <DFHack.h>

#define DTM_COL_COUNT 4

class dwarfTableModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	dwarfTableModel(QObject *parent = 0);
	~dwarfTableModel(void);
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role) const;
	QVariant headerData(int section, Qt::Orientation orientation,
		int role = Qt::DisplayRole) const;
	void attach(DFHack::Context *nDF);
	void detatch();
//TODO add getData(int id) function
public slots:
	void update(const int &numCreatures);

private:
	std::vector<DFHack::t_creature> creatures;
	DFHack::Context *DF;
	DFHack::Materials *Materials;
	DFHack::Translation *Tran;
	DFHack::Creatures *Creatures;
	DFHack::memory_info *mem;
	bool attached;
};

#endif
