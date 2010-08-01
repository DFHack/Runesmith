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
		std::vector<QString> const& labours = getLabourCache();
		return labours.size();
	}
	else
		return 0;
}

QVariant labTableModel::data(const QModelIndex &index, int role) const
{
	if((!creature) || (role != Qt::DisplayRole))
		return QVariant();	

	std::vector<QString> const& labours = getLabourCache();

	if(index.row() > labours.size())
		return QVariant();

	if(index.column())
		return QVariant();
	else
		return labours[index.row()];
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

void labTableModel::setCreature(RSCreature* nCreature)
{
	if(nCreature)
	{
		creature = nCreature;
	}
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