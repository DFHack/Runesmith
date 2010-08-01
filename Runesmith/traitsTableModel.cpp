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
		std::vector<QString> const& traits = creature->getTraitCache();
		return traits.size();
	}
	else
		return 0;
}

QVariant traitsTableModel::data(const QModelIndex &index, int role) const
{
	if((!creature) || (!DFI) || (role != Qt::DisplayRole))
		return QVariant();	

	std::vector<QString> const& traits = creature->getTraitCache();

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

void traitsTableModel::setCreature(RSCreature* nCreature)
{
	if(nCreature)
		creature = nCreature;
	else
	{
		creature = NULL;
		return;
	}
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
	if(index.column() == 0)
	{
		uint32_t temp = value.toUInt();
		std::vector<QString> const& traits = creature->getTraitCache();

		if(temp > 5)
			return false;
		else
			creature->editTrait(traits[index.row()].id, temp);

		return true;
	}
	else
		return false;
}

unsigned int traitsTableModel::getTraitIndex(unsigned int id)
{
	return traits[id].index;
}

RSCreature* traitsTableModel::getCreature()
{
	return creature;
}

bool traitsTableModel::addTrait(int index1, int index2)
{
	if((index1 >= 0) && (index2 >= 0))
	{
		if(index2 > 5)
			return false;
		else
			creature->editTrait(traits[index1].id, index2);
	}
	else
		return false;
}
