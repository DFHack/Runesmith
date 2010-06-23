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
		return traits.size();
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
		return traits[index.row()].text;
		
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

	updateCache();
}

Qt::ItemFlags traitsTableModel::flags(const QModelIndex & index) const
{
	if (!index.isValid())
		return Qt::NoItemFlags;

	if(!index.column())
	{
		return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
	}
	else
		return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

bool traitsTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if(!DFI)
		return false;

	if(!DFI->isAttached())
		return false;

	if(index.column() == 0)
	{
		uint32_t temp = value.toUInt();

		switch(temp)
		{
		case 0: creature->defaultSoul.traits[traits[index.row()].index] = 9; break;
		case 1: creature->defaultSoul.traits[traits[index.row()].index] = 24; break;
		case 2: creature->defaultSoul.traits[traits[index.row()].index] = 60; break;
		case 3: creature->defaultSoul.traits[traits[index.row()].index] = 75; break;
		case 4: creature->defaultSoul.traits[traits[index.row()].index] = 90; break;
		case 5: creature->defaultSoul.traits[traits[index.row()].index] = 100; break;
		default: return false;
		}

		DFI->setTraitsChanged(creature->id);
		updateCache();
		return true;
	}
	else
		return false;
}

unsigned int traitsTableModel::getTraitIndex(unsigned int id)
{
	return traits[id].index;
}

void traitsTableModel::updateCache()
{
	traits.clear();

	for(unsigned int i=0; i<NUM_TRAITS; i++)
	{
		TraitIndexItem temp;
		temp.text = DFI->translateTrait(i, creature->defaultSoul.traits[i]);
		temp.index = i;
		
		if(temp.text != "")
			traits.push_back(temp);
	}

	reset();
	emit dataChanged(QAbstractItemModel::createIndex(0, 0), 
			QAbstractItemModel::createIndex(
			colCount, rowCount()));
}

DFHack::t_creature *traitsTableModel::getCreature()
{
	return creature;
}

bool traitsTableModel::addTrait(int index1, int index2)
{
	if(!DFI)
		return false;

	if(!DFI->isAttached())
		return false;

	if((index1 >= 0) && (index2 >= 0))
	{
		switch(index2)
		{
		case 0: creature->defaultSoul.traits[index1] = 9; break;
		case 1: creature->defaultSoul.traits[index1] = 24; break;
		case 2: creature->defaultSoul.traits[index1] = 60; break;
		case 3: creature->defaultSoul.traits[index1] = 75; break;
		case 4: creature->defaultSoul.traits[index1] = 90; break;
		case 5: creature->defaultSoul.traits[index1] = 100; break;
		default: return false;
		}

		DFI->setTraitsChanged(creature->id);
		updateCache();
		return true;
	}
	else
		return false;
}
