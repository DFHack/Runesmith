#include <string>
#include <QColor>
#include "creatureTableModel.h"

creatureTableModel::creatureTableModel(QObject *parent) 
: dwarfTableModel(parent, 5)
{
}

creatureTableModel::~creatureTableModel(void)
{
}

int creatureTableModel::rowCount(const QModelIndex &parent) const
{
	if(!DFI)
		return 0;

	std::vector<RSCreature*>& creatures = DFI->getCreatures();
	return creatures.size();
}

QVariant creatureTableModel::data(const QModelIndex &index, int role) const
{
	if(!DFI)
		return QVariant();

	if(!DFI->isAttached())
		return QVariant();

	std::vector<RSCreature*>& creatures = DFI->getCreatures();

	if(index.row() >= creatures.size())
		return QVariant();

	QString transName;

	if(role == Qt::DisplayRole)
	{
		switch(index.column())
		{
		case 0:
			return creatures[index.row()]->getRace();

		case 1:				 
			transName = creatures[index.row()]->getDwarvishName();
		
			if(transName[0] == 0)
				return QVariant();
			return transName;

		case 2:
			return creatures[index.row()]->getProfession();

		case 3:
			return creatures[index.row()]->getFormattedHappiness();

		case 4:
			return creatures[index.row()]->getStatus();

		default:
			return QVariant();
		}
	}
	else if((role == Qt::BackgroundColorRole) && (index.column() == 3))
	{
		int green = creatures[index.row()]->getHappiness() + HAPPINESS_WEIGHT;
		if(green > 255)
			green = 255;		
		return QColor(255-green, green, 0);
	}
	else
		return QVariant();
}

QVariant creatureTableModel::headerData(int section,
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
			return QString("Race");

		case 1:
			return QString("Name");			

		case 2:
			return QString("Profession");			

		case 3:
			return QString("Happiness");			

		case 4:
			return QString("Status");

		default:
			return QVariant();
		}
	}
	else
		return QVariant();
}

Qt::ItemFlags creatureTableModel::flags(const QModelIndex & index) const
{
	if (!index.isValid())
		return Qt::NoItemFlags;

	if (index.column() == 3)
	{
		return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
	}
	else
		return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

bool creatureTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if(index.column() != 3)
		return false;

	if(!DFI)
		return false;

	if(!DFI->isAttached())
		return false;
	
	std::vector<RSCreature*>& creatures = DFI->getCreatures();	

	if(index.row() >= creatures.size())
		return false;

	uint32_t temp = value.toUInt();	
	creatures[index.row()]->setHappiness(temp);
	return true;
}
