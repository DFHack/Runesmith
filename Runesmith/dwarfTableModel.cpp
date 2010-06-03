#include <string>
#include <modules/Translation.h>
#include "dwarfTableModel.h"

dwarfTableModel::dwarfTableModel(DFHack::API & nDF, QObject *parent = 0) 
	: QAbstractTableModel(parent), DF(nDF)
{
}

dwarfTableModel::~dwarfTableModel(void)
{
}

int dwarfTableModel::rowCount(const QModelIndex &parent = QModelIndex()) const
{
	return creatures.size();
}

int dwarfTableModel::columnCount(const QModelIndex &parent = QModelIndex()) const
{
	return DTM_COL_COUNT
}

QVariant dwarfTableModel::data(const QModelIndex &index, int role) const
{
	if((index.row() >= creatures.size()) || (role != Qt::DisplayRole))
		return QVariant();

	switch(index.column())
	{
	case 0:
		DFHack::Translation *Tran = DF.getTranslation();
		std::string transName = Tran->TranslateName(creatures[index.row].name, false);
		return QString(creatures[index.row].name.first_name[0] + " " + transName);		
		 
	default:
		return QVariant();
	}
}

QVariant dwarfTableModel::headerData
	(int section, Qt::Orientation orientation,int role = Qt::DisplayRole) const
{
	if (role != Qt::DisplayRole)
		return QVariant();

	if(orientation == Qt::Horizontal)
	{
		switch(section)
		{
		case 0:
			return QString("Name");
			break;

		case 1:
			return QString("Profession");
			break;

		case 2:
			return QString("Happiness");
			break;

		case 3:
			return QString("Skills");
			break;
		}
	}
	else
		return QVariant();
}

void dwarfTableModel::update(DFHack::Creatures &Creatures)
{
}
