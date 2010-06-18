#include "labTableModel.h"

labTableModel::labTableModel(QObject *parent) : skillsTableModel(parent, 1)
{
}

labTableModel::~labTableModel(void)
{
}

int labTableModel::rowCount(const QModelIndex &parent) const
{
	if(creature)
	{
		return labours.size();
	}
	else
		return 0;
}

QVariant labTableModel::data(const QModelIndex &index, int role) const
{
	if((!creature) || (!DFI) || (role != Qt::DisplayRole))
		return QVariant();	

	if(index.row() > labours.size())
		return QVariant();

	if(index.column())
		return QVariant();
	else
		return DFI->translateLabour(labours[index.row()]);
}

QVariant labTableModel::headerData(int section,
									Qt::Orientation orientation,
									int role) const
{
	if (role != Qt::DisplayRole)
		return QVariant();

	if(orientation == Qt::Horizontal)
	{
		if(section)
			return QVariant();
		else
			return "Labours";
	}
	else
		return QVariant();
}

void labTableModel::setCreature(DFInterface *nDFI, DFHack::t_creature *nCreature)
{
	DFI = nDFI;	

	if(nCreature)
		creature = nCreature;
	else
	{
		creature = NULL;
		return;
	}

	labours.clear();

	for(unsigned int i=0; i<NUM_CREATURE_LABORS; i++)
	{
		if(!creature->labors[i])
			continue;

		labours.push_back(i);
	}

	reset();
	emit dataChanged(QAbstractItemModel::createIndex(0, 0), 
			QAbstractItemModel::createIndex(
			colCount, rowCount()));
}