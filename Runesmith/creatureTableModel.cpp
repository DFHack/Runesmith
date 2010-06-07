#include "creatureTableModel.h"

creatureTableModel::creatureTableModel(QObject *parent) 
	: dwarfTableModel(parent, 5)
{
}

creatureTableModel::~creatureTableModel(void)
{
}

void creatureTableModel::update(const int &numCreatures)
{
	if(attached)
	{
		creatures.clear();

		for(int i=0; i<numCreatures; i++)
		{
			DFHack::t_creature temp;
			Creatures->ReadCreature(i,temp);			
			creatures.push_back(temp);
		}
		
		reset();
		emit dataChanged(QAbstractItemModel::createIndex(0, 0), 
			QAbstractItemModel::createIndex(colCount, creatures.size()));
	}
}

QVariant creatureTableModel::data(const QModelIndex &index, int role) const
{
	if(!attached)
		return QVariant();

	if((index.row() >= creatures.size()) || (role != Qt::DisplayRole))
		return QVariant();
	
	QString transName;

	switch(index.column())
	{
	case 0:
		return QString(Materials->raceEx[creatures[index.row()].race].rawname);
	case 1:		
		transName = creatures[index.row()].name.first_name;
		transName.append(" ");
		transName.append(Tran->TranslateName
			(creatures[index.row()].name, false).c_str());
		return transName;
	
	case 2:
		return QString(mem->getProfession(creatures[index.row()].profession).c_str());

	case 3:
		return QString(QString::number(creatures[index.row()].happiness));

	case 4:
		//TODO make this general status instead of just mood
		switch(creatures[index.row()].mood)
		{
		case -1:
			return QVariant();

		case 0:
			return QString("Fey");

		case 1:
			return QString("Possesed");

		case 2:
		case 3:
		case 4:
			return QVariant();

		case 5:
			return QString("Melancholy/Beserk");
		}		
		 
	default:
		return QVariant();
	}
}

QVariant creatureTableModel::headerData
	(int section, Qt::Orientation orientation,int role) const
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
