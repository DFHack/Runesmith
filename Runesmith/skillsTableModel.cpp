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
		return creature->defaultSoul.numSkills;
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
	
	QString temp;

	switch(index.column())
	{
	case 0:
		return DFI->translateSkill(creature->defaultSoul.skills[index.row()].id);

	case 1:		
		temp.append(
			DFI->getLevelInfo(
			creature->defaultSoul.skills[index.row()].rating).name.c_str());
		temp.append(" [");
		temp.append(
			QString::number(
			DFI->getLevelInfo(creature->defaultSoul.skills[index.row()].rating).level));
		temp.append("]");
		return temp;

	case 2:		
		return QString(
			QString::number(creature->defaultSoul.skills[index.row()].experience));

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
		return Qt::ItemFlag::NoItemFlags;

	if (index.column() == 1)
	{
		return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemFlag::ItemIsEditable;
	}
	else
		return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

bool skillsTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	return false;
}
