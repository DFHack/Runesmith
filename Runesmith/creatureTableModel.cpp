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

	std::vector<DFHack::t_creature>& creatures = DFI->getCreatures();
	return creatures.size();
}

QVariant creatureTableModel::data(const QModelIndex &index, int role) const
{
	if(!DFI)
		return QVariant();

	if(!DFI->isAttached())
		return QVariant();

	std::vector<DFHack::t_creature>& creatures = DFI->getCreatures();

	if(index.row() >= creatures.size())
		return QVariant();

	QString transName;

	if(role == Qt::DisplayRole)
	{
		switch(index.column())
		{
		case 0:
			return QString(DFI->translateRace(creatures[index.row()].race));

		case 1:		
			transName = creatures[index.row()].name.first_name;
			transName.append(" ");
			transName.append(DFI->translateName(creatures[index.row()].name));
			return transName;

		case 2:
			return QString(DFI->translateProfession(creatures[index.row()].profession));

		case 3:
			if (creatures[index.row()].happiness < 1)
				transName = "Miserable";
			else if (creatures[index.row()].happiness <= 25)
				transName = "Very Unhappy";
			else if (creatures[index.row()].happiness <= 50)
				transName = "Unhappy";
			else if (creatures[index.row()].happiness <= 75)
				transName = "Fine";
			else if (creatures[index.row()].happiness <= 125)
				transName = "Content";
			else if (creatures[index.row()].happiness <= 150)
				transName = "Happy";
			else
				transName = "Ecstatic";
			transName.append(" [");
			transName.append(QString::number(creatures[index.row()].happiness));
			return transName.append("]");

		case 4:
			//TODO make this general status instead of just mood
			if(creatures[index.row()].flags1.bits.dead)
				return "Dead";

			switch(creatures[index.row()].mood)
			{
			case -1: return QVariant();
			case 0: return QString("Fey");
			case 1: return QString("Possesed");
			case 2:
			case 3:
			case 4: return QVariant();
			case 5:	return QString("Melancholy/Beserk");
			}		

		default:
			return QVariant();
		}
	}
	else if((role == Qt::BackgroundColorRole) && (index.column() == 3))
	{
		int green = creatures[index.row()].happiness + HAPPINESS_WEIGHT;
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
