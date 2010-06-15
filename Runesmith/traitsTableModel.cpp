#include "traitsTableModel.h"

traitsTableModel::traitsTableModel(QObject *parent) : skillsTableModel(parent, 1)
{
}

traitsTableModel::~traitsTableModel(void)
{
}

int traitsTableModel::rowCount(const QModelIndex &parent) const
{
	if(creature)
	{
		traits.size();
	}
	else
		return 0;
}

QVariant traitsTableModel::data(const QModelIndex &index, int role) const
{
	if((!creature) || (!DFI) || (role != Qt::DisplayRole))
		return QVariant();	

	if(index.row() > traits.size())
		return QVariant();

	switch(index.column())
	{
	case 0:
		return traits[index.row()];
		
	default:
		return QVariant();
	}
}

QVariant traitsTableModel::headerData(int section,
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
			return QString("Traits");			

		default:
			return QVariant();
		}
	}
	else
		return QVariant();
}

void traitsTableModel::setCreature(DFInterface *nDFI,
								   DFHack::t_creature *nCreature)
{
	DFI = nDFI;
	
	if(nCreature)
		creature = nCreature;
	else
	{
		creature = NULL;
		return;
	}

	for(int i=0; i<NUM_TRAITS; i++)
	{
		QString temp = DFI->translateTrait(i, creature->defaultSoul.traits[i]);
		
		if(temp != "")
			traits.push_back(temp);
	}

	reset();
	emit dataChanged(QAbstractItemModel::createIndex(0, 0), 
			QAbstractItemModel::createIndex(
			colCount, rowCount()));
}
