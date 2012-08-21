#include <string>
#include <limits>
#include <QColor>
#include "dwarfTableModel.h"

dwarfTableModel::dwarfTableModel(QObject *parent, int nColCount) 
	: QAbstractTableModel(parent), colCount(nColCount), DFI(NULL)
{	
}

dwarfTableModel::~dwarfTableModel(void)
{
}

int dwarfTableModel::rowCount(const QModelIndex &parent) const
{
	if(!DFI)
		return 0;

	std::vector<RSCreature*>& dwarves = DFI->getDwarves();
	return dwarves.size();
}

int dwarfTableModel::columnCount(const QModelIndex &parent) const
{
	return colCount;
}

QVariant dwarfTableModel::data(const QModelIndex &index, int role) const
{
	if(!DFI)
		return QVariant();

	if(!DFI->isAttached())
		return QVariant();
	
	std::vector<RSCreature*>& dwarves = DFI->getDwarves();	

	if(index.row() >= dwarves.size())
		return QVariant();

	if(role == Qt::DisplayRole)
	{
		switch(index.column())
		{
		case 0:
			return dwarves[index.row()]->getDwarvishName();

		case 1:
			return dwarves[index.row()]->getProfession();

		case 2:
			return dwarves[index.row()]->getFormattedHappiness();

		case 3:
			return dwarves[index.row()]->getStatus();

		default:
			return QVariant();
		}
	}
	else if((role == Qt::BackgroundColorRole) && (index.column() == 2))
	{
		int green = dwarves[index.row()]->getHappiness() + HAPPINESS_WEIGHT;
		if(green > 255)
			green = 255;		
		return QColor(255-green, green, 0);
	}
	else
		return QVariant();
}

QVariant dwarfTableModel::headerData
	(int section, Qt::Orientation orientation,int role) const
{
	if (role != Qt::DisplayRole)
		return QVariant();

	if(orientation == Qt::Horizontal)
	{
		switch(section)
		{
		case 0:
			return QString("Name");			

		case 1:
			return QString("Profession");			

		case 2:
			return QString("Happiness");			

		case 3:
			return QString("Status");

		default:
			return QVariant();
		}
	}
	else
		return QVariant();
}

void dwarfTableModel::update(DFInterface *nDFI)
{
	DFI = nDFI;
	reset();
	emit dataChanged(QAbstractItemModel::createIndex(0, 0), 
		QAbstractItemModel::createIndex(colCount, rowCount()));
}

Qt::ItemFlags dwarfTableModel::flags(const QModelIndex & index) const
{
	if (!index.isValid())
		return Qt::NoItemFlags;

	if (index.column() == 2)
	{
		return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
	}
	else
		return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

bool dwarfTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if(index.column() != 2)
		return false;

	if(!DFI)
		return false;

	if(!DFI->isAttached())
		return false;
	
	std::vector<RSCreature*>& dwarves = DFI->getDwarves();	

	if(index.row() >= dwarves.size())
		return false;

	uint32_t temp = value.toUInt();	
	dwarves[index.row()]->setHappiness(temp);
	return true;
}

void dwarfTableModel::sort(int column, Qt::SortOrder order)
{
	switch(column)
	{
	case 0:
		if(order == Qt::AscendingOrder)
			DFI->sortDwarvesByName(false);
		else
			DFI->sortDwarvesByName(true);
		break;

	case 1:
		if(order == Qt::AscendingOrder)
			DFI->sortDwarvesByProf(false);
		else
			DFI->sortDwarvesByProf(true);
		break;

	case 2:
		if(order == Qt::AscendingOrder)
			DFI->sortDwarvesByHap(false);
		else
			DFI->sortDwarvesByHap(true);
		break;
	}

	emit dataChanged(QAbstractItemModel::createIndex(0, 0), 
		QAbstractItemModel::createIndex(colCount, rowCount()));
}
