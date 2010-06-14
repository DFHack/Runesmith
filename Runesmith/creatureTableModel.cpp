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

	std::vector<DFHack::t_creature *>& creatures = DFI->getCreatures();
	return creatures.size();
}

QVariant creatureTableModel::data(const QModelIndex &index, int role) const
{
	if(!DFI)
		return QVariant();

	if(!DFI->isAttached())
		return QVariant();

	std::vector<DFHack::t_creature *>& creatures = DFI->getCreatures();

	if(index.row() >= creatures.size())
		return QVariant();

	QString transName;

	if(role == Qt::DisplayRole)
	{
		switch(index.column())
		{
		case 0:
			return QString(DFI->translateRace(creatures[index.row()]->race));

		case 1:		
			transName = creatures[index.row()]->name.first_name;
			transName.append(" ");
			transName.append(DFI->translateName(creatures[index.row()]->name));
			return transName;

		case 2:
			return QString(DFI->translateProfession(creatures[index.row()]->profession));

		case 3:
			if (creatures[index.row()]->happiness < 1)
				transName = "Miserable";
			else if (creatures[index.row()]->happiness <= 25)
				transName = "Very Unhappy";
			else if (creatures[index.row()]->happiness <= 50)
				transName = "Unhappy";
			else if (creatures[index.row()]->happiness <= 75)
				transName = "Fine";
			else if (creatures[index.row()]->happiness <= 125)
				transName = "Content";
			else if (creatures[index.row()]->happiness <= 150)
				transName = "Happy";
			else
				transName = "Ecstatic";
			transName.append(" [");
			transName.append(QString::number(creatures[index.row()]->happiness));
			return transName.append("]");

		case 4:
			//TODO finish moods
			if(creatures[index.row()]->flags1.bits.dead)
				return "Dead";
			
			switch(creatures[index.row()]->mood)
			{
			case 0: transName = "( Fey ) "; break;
			case 1: transName = "( Possesed ) "; break;
			//case 2:
			//case 3:
			//case 4: 
			case 5:	transName = "( Melancholy/Beserk ) "; break;
			}

			if(creatures[index.row()]->flags1.bits.drowning)
				transName.append("( Drowning ) ");

			if(creatures[index.row()]->flags2.bits.for_trade)
				transName.append("( For Trade )");

			if(creatures[index.row()]->flags2.bits.slaughter)
				transName.append("( For Slaughter )");

			if(creatures[index.row()]->flags2.bits.breathing_problem)
				transName.append("( Breathing Problem )");

			if(creatures[index.row()]->flags2.bits.vision_damaged)
				transName.append("( Vision Damaged )");

			if(creatures[index.row()]->flags2.bits.vision_missing)
				transName.append("( Vision Missing )");

			if(creatures[index.row()]->flags1.bits.chained)
				transName.append("( Chanined ) ");

			if(creatures[index.row()]->flags1.bits.caged)
				transName.append("( Caged ) ");

			if(creatures[index.row()]->flags1.bits.invades)
				transName.append("( Invading )");

			if(creatures[index.row()]->flags1.bits.hidden_in_ambush)
				transName.append("( Hidden in Ambush )");

			if(creatures[index.row()]->flags2.bits.sparring)
				transName.append("( Sparring )");

			if(creatures[index.row()]->flags2.bits.swimming)
				transName.append("( Swimming )");

			if(creatures[index.row()]->flags2.bits.visitor || 
				creatures[index.row()]->flags2.bits.visitor_uninvited)
				transName.append("( Visitor )");

			return transName;

		default:
			return QVariant();
		}
	}
	else if((role == Qt::BackgroundColorRole) && (index.column() == 3))
	{
		int green = creatures[index.row()]->happiness + HAPPINESS_WEIGHT;
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
		return Qt::ItemFlag::NoItemFlags;

	if (index.column() == 3)
	{
		return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemFlag::ItemIsEditable;
	}
	else
		return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

bool creatureTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	return false;
}
