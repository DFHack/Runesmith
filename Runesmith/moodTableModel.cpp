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
		if(creature->mood != -1)
		{
			std::vector<DFHack::t_material> &mats = DFI->getMoodMats(creature->id);
			return mats.size()+2;
		}
		else
			return 2;
	}
	else
		return 0;
}

QVariant moodTableModel::data(const QModelIndex &index, int role) const
{
	if((!creature) || (!DFI) || (role != Qt::DisplayRole))
		return QVariant();

	if(creature->mood < 0)
	{
		if(!index.row())
		{
			if(index.column())
				return "None";
			else
				return "Mood:";
		}
		else if(index.row() == 1)
		{
			if(!index.column())				
				return "Mood Skill:";
			else
				return " ";
		}
		else
			return QVariant();
	}

	switch(index.column())
	{
	case 0:
		if(index.row() == 0)
			return "Mood:";
		else if(index.row() == 1)
			return "Mood Skill:";
		else
		{			
			std::vector<DFHack::t_material> &mats = DFI->getMoodMats(creature->id);

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
			return DFI->getMood(creature->mood);
		else if(index.row() == 1)
			return DFI->translateSkill(creature->mood_skill);
		else
		{		
			std::vector<DFHack::t_material> &mats = DFI->getMoodMats(creature->id);

			if(index.row()-2 < mats.size())
			{
				return DFI->getMatDescription((DFHack::t_material&)mats[(index.row()-2)]);
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

	if((index.column() == 1) && ((index.row() == 0) || (index.row() == 1)))
	{
		return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
	}
	else
		return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

bool moodTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if(!DFI)
		return false;

	if(!DFI->isAttached())
		return false;

	if(index.column() == 1)
	{
		int temp = value.toInt();

		if(index.row() == 0)
		{			
			creature->mood = temp-1;

			if(creature->mood == -1)
			{
				if(creature->flags1.bits.has_mood)
					creature->flags1.bits.has_mood = 0;
				DFI->setFlagsChanged(creature->id);
			}
			else
			{
				if(!creature->flags1.bits.has_mood)
					creature->flags1.bits.has_mood = 1;
				DFI->setFlagsChanged(creature->id);

				if(creature->mood != -1)
					std::vector<DFHack::t_material> &mats = DFI->getMoodMats(creature->id);
			}

			DFI->setMoodChanged(creature->id);
			return true;
		}	
		else if(index.row() == 1)
		{
			creature->mood_skill = creature->defaultSoul.skills[temp].id;
			DFI->setMoodChanged(creature->id);
		}
		else
			return false;
	}
	else
		return false;
}

void moodTableModel::setCreature(DFInterface *nDFI,
								 DFHack::t_creature *nCreature)
{
	DFI = nDFI;

	if(nCreature)
		creature = nCreature;
	else
	{
		creature = NULL;
		return;
	}	

	if(creature->mood != -1)
		std::vector<DFHack::t_material> &mats = DFI->getMoodMats(creature->id);
	reset();
	emit dataChanged(QAbstractItemModel::createIndex(0, 0), 
		QAbstractItemModel::createIndex(
		colCount, rowCount()));
}
