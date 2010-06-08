#include "attrTableModel.h"

attrTableModel::attrTableModel(QObject *parent) : skillsTableModel(parent)
{
}

attrTableModel::~attrTableModel(void)
{
}

int attrTableModel::rowCount(const QModelIndex &parent) const
{
	if(creature)
	{
		return NUM_ATTRS;
	}
	else
		return 0;
}

QVariant attrTableModel::data(const QModelIndex &index, int role) const
{
	if((!creature) || (!DFI) || (role != Qt::DisplayRole))
		return QVariant();	

	switch(index.column())
	{
	case 0:
		switch(index.row())
		{
		case 0: return QString("Strength");
		case 1: return QString("Agility");
		case 2: return QString("Toughness");
		case 3: return QString("Endurance");
		case 4: return QString("Recuperation");
		case 5: return QString("Disease Resistance");
		case 6: return QString("Willpower");
		case 7: return QString("Memory");
		case 8: return QString("Focus");
		case 9: return QString("Intuition");
		case 10: return QString("Patience");
		case 11: return QString("Creatvity");
		case 12: return QString("Musicality");
		case 13: return QString("Analytical Ability");
		case 14: return QString("Linguistic Ability");
		case 15: return QString("Spatial Sense");
		case 16: return QString("Kinesthetic Sense");
		case 17: return QString("Social Awareness");
		default: return QVariant();
		}

	case 1:
		switch(index.row())
		{
		case 0: return QString(QString::number(creature->strength.level));
		case 1: return QString(QString::number(creature->agility.level));
		case 2: return QString(QString::number(creature->toughness.level));
		case 3: return QString(QString::number(creature->endurance.level));
		case 4: return QString(QString::number(creature->recuperation.level));
		case 5: return QString(QString::number(creature->disease_resistance.level));
		case 6: return QString(QString::number(creature->defaultSoul.willpower.level));
		case 7: return QString(QString::number(creature->defaultSoul.memory.level));
		case 8: return QString(QString::number(creature->defaultSoul.focus.level));
		case 9: return QString(QString::number(creature->defaultSoul.intuition.level));
		case 10: return QString(QString::number(creature->defaultSoul.patience.level));
		case 11: return QString(QString::number(creature->defaultSoul.creativity.level));
		case 12: return QString(QString::number(creature->defaultSoul.musicality.level));
		case 13: return QString(QString::number(creature->defaultSoul.analytical_ability.level));
		case 14: return QString(QString::number(creature->defaultSoul.linguistic_ability.level));
		case 15: return QString(QString::number(creature->defaultSoul.spatial_sense.level));
		case 16: return QString(QString::number(creature->defaultSoul.kinesthetic_sense.level));
		case 17: return QString(QString::number(creature->defaultSoul.social_awareness.level));
		default: return QVariant();
		}

	default:
		return QVariant();
	}
}

QVariant attrTableModel::headerData(int section,
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
			return QString("Attribute");			

		case 1:
			return QString("Rating");

		default:
			return QVariant();
		}
	}
	else
		return QVariant();
}
