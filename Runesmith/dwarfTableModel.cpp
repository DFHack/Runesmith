#include <string>
#include "dwarfTableModel.h"

dwarfTableModel::dwarfTableModel(QObject *parent) 
	: QAbstractTableModel(parent), attached(false), DF(NULL), Creatures(NULL),
	Tran(NULL), Materials(NULL)
{	
}

dwarfTableModel::~dwarfTableModel(void)
{
	creatures.clear();
}

int dwarfTableModel::rowCount(const QModelIndex &parent) const
{
	return creatures.size();
}

int dwarfTableModel::columnCount(const QModelIndex &parent) const
{
	return DTM_COL_COUNT;
}

QVariant dwarfTableModel::data(const QModelIndex &index, int role) const
{
	if(!attached)
		return QVariant();

	if((index.row() >= creatures.size()) || (role != Qt::DisplayRole))
		return QVariant();
	
	QString transName;

	switch(index.column())
	{
	case 0:		
		transName = creatures[index.row()].name.first_name;
		transName.append(" ");
		transName.append(Tran->TranslateName
			(creatures[index.row()].name, false).c_str());
		return transName;
	
	case 1:
		return QString(mem->getProfession(creatures[index.row()].profession).c_str());

	case 2:
		return QString(QString::number(creatures[index.row()].happiness));

	case 3:
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
		/*case 3:
		for(int i=0; i<creatures[index.row()].defaultSoul.numSkills; i++)
		{
			transName.append(
				mem->getSkill(creatures[index.row()].defaultSoul.skills[i].id).c_str());
			transName.append('[');
			transName.append(
				QString::number(creatures[index.row()].defaultSoul.skills[i].rating));
			transName.append("]  ");
		}

		return transName;*/
		 
	default:
		return QVariant();
	}
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
		}
	}
	else
		return QVariant();
}

void dwarfTableModel::update(const int &numCreatures)
{
	if(attached)
	{
		creatures.clear();

		for(int i=0; i<numCreatures; i++)
		{
			DFHack::t_creature temp;
			Creatures->ReadCreature(i,temp);

			if(std::string(Materials->raceEx[temp.race].rawname) == "DWARF")
			{
				creatures.push_back(temp);
			}
		}
		
		emit dataChanged(QAbstractItemModel::createIndex(0, 0), 
			QAbstractItemModel::createIndex(3, creatures.size()));
	}
}

void dwarfTableModel::attach(DFHack::Context *nDF)
{
	if(nDF)
	{
		DF = nDF;
		attached = true;
		Creatures = DF->getCreatures();
		Materials = DF->getMaterials();
		Tran = DF->getTranslation();
		mem = DF->getMemoryInfo();
	}
}

void dwarfTableModel::detatch()
{
	creatures.clear();
	attached = false;
	emit dataChanged(QAbstractItemModel::createIndex(0, 0), 
		QAbstractItemModel::createIndex(3, creatures.size()));
}
