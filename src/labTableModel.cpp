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
		std::vector<cacheItem> const& labours = creature->getLabourCache();
		return labours.size();
	}
	else
		return 0;
}

QVariant labTableModel::data(const QModelIndex &index, int role) const
{
	if((!creature) || (role != Qt::DisplayRole))
		return QVariant();	

	std::vector<cacheItem> const& labours = creature->getLabourCache();

	if(index.row() > labours.size())
		return QVariant();

	if(index.column())
		return QVariant();
	else
		return labours[index.row()].text;
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

bool labTableModel::addLabour(unsigned int index)
{
	bool retVal = creature->addLabour(index);

	if(retVal)
	{
		reset();
		emit dataChanged(QAbstractItemModel::createIndex(0, 0), 
			QAbstractItemModel::createIndex(colCount, rowCount()));
	}

	return retVal;
}

bool labTableModel::removeLabours(QModelIndexList indexes)
{
	bool retVal;

	for(int i=0; i<indexes.count(); i++)
	{
		QModelIndex index = indexes.at(i);
		retVal = creature->removeTopLabour();

		if(!retVal)
			return retVal;
	}
	
	reset();
	emit dataChanged(QAbstractItemModel::createIndex(0, 0), 
		QAbstractItemModel::createIndex(colCount, rowCount()));

	return retVal;
}