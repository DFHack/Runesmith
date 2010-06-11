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
		labours.size();
	}
	else
		return 0;
}

QVariant labTableModel::data(const QModelIndex &index, int role) const
{
	if((!creature) || (!DFI) || (role != Qt::DisplayRole))
		return QVariant();	

	if(index.row() >= labours.size())
		return QVariant();

	switch(index.column())
	{
	case 0:
		return DFI->translateLabour(labours[index.row()]);
	default:
		return QVariant();
	}
}

QVariant labTableModel::headerData(int section,
									Qt::Orientation orientation,
									int role) const
{
	if (role != Qt::DisplayRole)
		return QVariant();

	if(orientation == Qt::Horizontal)
	{
		switch(section)
		{
		case 0:
			return QString("Labours");	

		default:
			return QVariant();
		}
	}
	else
		return QVariant();
}

void labTableModel::setCreature(DFInterface *nDFI, const DFHack::t_creature *nCreature)
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