#ifndef DWARFTABLEMODEL_H
#define DWARFTABLEMODEL_H

#include <QAbstractTableModel>
#include <vector>
#include <DFHack.h>

class dwarfTableModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	dwarfTableModel(QObject *parent = 0, int nCols = 4);
	~dwarfTableModel(void);
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;
	virtual QVariant data(const QModelIndex &index, int role) const;
	virtual QVariant headerData(int section, Qt::Orientation orientation,
		int role = Qt::DisplayRole) const;
	void attach(DFHack::Context *nDF);
	void detatch();
	const DFHack::t_creature* getCreatureP(int id); 

public slots:
	virtual void update(const int &numCreatures);

protected:
	const int colCount;
	std::vector<DFHack::t_creature> creatures;
	DFHack::Context *DF;
	DFHack::Materials *Materials;
	DFHack::Translation *Tran;
	DFHack::Creatures *Creatures;
	DFHack::memory_info *mem;
	bool attached;
};

#endif
