#include "moodTableModel.h"

moodTableModel::moodTableModel(QObject *parent) : skillsTableModel(parent, 2)
{
}

moodTableModel::~moodTableModel(void)
{
}

int moodTableModel::rowCount(const QModelIndex &parent) const
{
	if(creature)
	{
		std::vector<QString> const& mats = creature->getJobMats();
		return mats.size()+2;
	}
	else
		return 0;
}

QVariant moodTableModel::data(const QModelIndex &index, int role) const
{
	if((!creature) || (!DFI) || (role != Qt::DisplayRole))
		return QVariant();

	switch(index.column())
	{
	case 0:
		if(index.row() == 0)
		{
			return "Mood:";
		}
		else if(index.row() == 1)
		{
			return "Mood Skill:";
		}
		else
		{			
			std::vector<QString> const& mats = creature->getJobMats();

			if(index.row()-2 < mats.size())
			{
				QString temp("Material ");
				temp.append(QString::number(index.row()-2));
				return temp;
			}
			else
				return QVariant();			
		}

	case 1:		
		if(index.row() == 0)
		{
			return creature->getMood();
		}
		else if(index.row() == 1)
		{
			return creature->getMoodSkill();
		}
		else
		{		
			std::vector<QString> const& mats = creature->getJobMats();

			if(index.row()-2 < mats.size())
			{
				return mats[index.row()-2];
			}
			else
				return QVariant();			
		}

	default:
		return QVariant();
	}
}

QVariant moodTableModel::headerData(int section,
									Qt::Orientation orientation,
									int role) const
{
	if (role != Qt::DisplayRole)
		return QVariant();

	if(orientation == Qt::Horizontal)
	{
		switch(section)
		{
		case 0: return "Field";
		case 1: return "Value";
		default: return QVariant();
		}
	}
	else
		return QVariant();
}

Qt::ItemFlags moodTableModel::flags(const QModelIndex & index) const
{
	if (!index.isValid())
		return Qt::NoItemFlags;

//	if((index.row() == 0) || (index.row() == 1)) // turned off material editing with this & in delegate
		return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
//	else
//		return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

bool moodTableModel::setData(const QModelIndex &index, 
							 const QVariant &value,
							 int role)
{
	if(index.column() == 1)
	{
		int temp = value.toInt();

		switch(index.row())
		{
		case 0:
			creature->setMood(temp-1);
			return true;			

		case 1:	
			creature->setMoodSkill(temp);
			return true;

		default:
			std::vector<DFHack::t_matgloss> const& organic = DFI->getOrganicMats();
			std::vector<DFHack::t_matgloss> const& inorganic = DFI->getInorgaincMats();

			/* use mats[i].index to get type from matgloss vector, thus change mats.index to change type.
		sub index needs to be set to between 416 & 618 for organic, subindex 0 looks like it may work for inorganic*/
			if(temp >= inorganic.size())
			{
				temp -= inorganic.size();
				creature->setMat(index.row()-2, temp, (const char*)&organic[temp].id, 420);
			}
			else
			{
				creature->setMat(index.row()-2, temp, (const char*)&inorganic[temp].id, 0);
			}
		
		}
	}
	else
		return false;
}
