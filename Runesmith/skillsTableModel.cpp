#include <limits>
#include "skillsTableModel.h"

skillsTableModel::skillsTableModel(QObject *parent, int nColCount) 
	: QAbstractTableModel(parent), creature(NULL), colCount(nColCount)
{
}

skillsTableModel::~skillsTableModel(void)
{
}

int skillsTableModel::rowCount(const QModelIndex &parent) const
{
	if(creature)
	{
		return creature->getNumSkills();
	}
	else
		return 0;
}

int skillsTableModel::columnCount(const QModelIndex &parent) const
{
	return colCount;
}

QVariant skillsTableModel::data(const QModelIndex &index, int role) const
{
	if((!creature) || (!DFI) || (role != Qt::DisplayRole))
		return QVariant();	
	
	std::vector<formattedSkill> const& temp = creature->getFormattedSkills();

	switch(index.column())
	{
	case 0:
		return temp[index.row()].skill;

	case 1:
		return temp[index.row()].level;

	case 2:		
		return temp[index.row()].xp;

	default:
		return QVariant();
	}
}

QVariant skillsTableModel::headerData(int section,
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
			return QString("Skill");			

		case 1:
			return QString("Rating");

		case 2:
			return QString("Progress (XP)");

		default:
			return QVariant();
		}
	}
	else
		return QVariant();
}

void skillsTableModel::setCreature(DFInterface *nDFI,
								   RSCreature* nCreature)
{
	DFI = nDFI;
	
	if(nCreature)
		creature = nCreature;
	else
	{
		creature = NULL;
		return;
	}

	reset();
	emit dataChanged(QAbstractItemModel::createIndex(0, 0), 
			QAbstractItemModel::createIndex(
			colCount, rowCount()));
}

void skillsTableModel::clear()
{
	creature = NULL;
	reset();
	emit dataChanged(QAbstractItemModel::createIndex(0, 0), 
			QAbstractItemModel::createIndex(
			colCount, rowCount()));	
}

int skillsTableModel::getNumCols()
{
	return colCount;
}

Qt::ItemFlags skillsTableModel::flags(const QModelIndex & index) const
{
	if (!index.isValid())
		return Qt::NoItemFlags;

	if((index.column() == 1) || (index.column() == 2))
	{
		return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
	}
	else
		return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

bool skillsTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if(!DFI)
		return false;

	if(!DFI->isAttached())
		return false;

	if(index.column() == 1)
	{
		uint32_t temp = value.toUInt();

		if(temp > std::numeric_limits<uint8_t>::max())
			temp = std::numeric_limits<uint8_t>::max();

		creature->setSkillLevel(index.row(), temp);
		return true;
	}		
	else if(index.column() == 2)
	{
		uint32_t temp = value.toUInt();

		if(temp > std::numeric_limits<uint16_t>::max())
			temp = std::numeric_limits<uint16_t>::max();

		creature->setSkillExperiance(index.row(), temp);
		return true;
	}
	else
		return false;
}
