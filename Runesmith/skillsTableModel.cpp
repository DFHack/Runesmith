#include "skillsTableModel.h"

skillsTableModel::skillsTableModel(QObject *parent) 
	: QAbstractTableModel(parent), creature(NULL), mem(NULL)
{
}

skillsTableModel::~skillsTableModel(void)
{
}

int skillsTableModel::rowCount(const QModelIndex &parent) const
{
	if(creature)
	{
		return creature->defaultSoul.numSkills;
	}
	else
		return 0;
}

int skillsTableModel::columnCount(const QModelIndex &parent) const
{
	return STM_COL_COUNT;
}

QVariant skillsTableModel::data(const QModelIndex &index, int role) const
{
	if((!creature) || (!mem) || (role != Qt::DisplayRole))
		return QVariant();	
	
	switch(index.column())
	{
	case 0:
		return QString(
			mem->getSkill(creature->defaultSoul.skills[index.row()].id).c_str());
	case 1:
		return QString(
			QString::number(creature->defaultSoul.skills[index.row()].rating));

	default:
		return QVariant();
	}
}

QVariant skillsTableModel::headerData(int section, Qt::Orientation orientation,
		int role) const
{
	if (role != Qt::DisplayRole)
		return QVariant();

	if(orientation == Qt::Horizontal)
	{
		switch(section)
		{
		case 0:
			return QString("Skill");			

		case 1:
			return QString("Rating");

		default:
			return QVariant();
		}
	}
	else
		return QVariant();
}

void skillsTableModel::setCreature(
	DFHack::Context *DF, const DFHack::t_creature *nCreature)
{
	if(DF)
		mem = DF->getMemoryInfo();
	else
		return;

	if(nCreature)
		creature = nCreature;
	else
		return;
	reset();
	emit dataChanged(QAbstractItemModel::createIndex(0, 0), 
			QAbstractItemModel::createIndex(
			STM_COL_COUNT, creature->defaultSoul.numSkills));
}
