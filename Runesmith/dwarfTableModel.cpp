#include <string>
#include "dwarfTableModel.h"

dwarfTableModel::dwarfTableModel(DFHack::API &nDF, QObject *parent) 
	: QAbstractTableModel(parent), DF(nDF)
{
	Creatures = DF.getCreatures();
    Materials = DF.getMaterials();
	Tran = DF.getTranslation();
}

dwarfTableModel::~dwarfTableModel(void)
{
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
	QString transName;

	if((index.row() >= creatures.size()) || (role != Qt::DisplayRole))
		return QVariant();

	switch(index.column())
	{
	case 0:		
		transName = Tran->TranslateName(creatures[index.row()].name, false).c_str();
		return QString(creatures[index.row()].name.first_name[0] + " " + transName);		
		 
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
			return QString("Skills");			
		}
	}
	else
		return QVariant();
}

void dwarfTableModel::update(const int &numCreatures)
{
	for(int i=0; i<numCreatures; i++)
    {
        DFHack::t_creature temp;
        Creatures->ReadCreature(i,temp);

		if(std::string(Materials->raceEx[temp.race].rawname) == "DWARF")
        {
            creatures.push_back(temp);
        }
    }
}
