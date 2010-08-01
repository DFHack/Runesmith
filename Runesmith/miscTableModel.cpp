#include <limits>
#include "miscTableModel.h"

miscTableModel::miscTableModel(QObject *parent) : skillsTableModel(parent, 2)
{
}

miscTableModel::~miscTableModel(void)
{
}

int miscTableModel::rowCount(const QModelIndex &parent) const
{
	if(creature)
	{
		return 11;
	}
	else
		return 0;
}

QVariant miscTableModel::data(const QModelIndex &index, int role) const
{
	if(!creature)
		return QVariant();

	switch(index.column())
	{
	case 0:
		if(role != Qt::DisplayRole)
			return QVariant();

		switch(index.row())
		{
		case 0: return QString("Player Civilisation");
		case 1:	return QString("Nickname:");	
		case 2:	return QString("English Name:");
		case 3:	return QString("Sex:");
		case 4:	return QString("DOB (D/M/Y):");
		case 5:	return QString("Age:");		
		case 6:	return QString("Custom Profession:");
		case 7: return QString("Position:");
		case 8: return QString("X");
		case 9: return QString("Y");
		case 10: return QString("Z");
		default: return QVariant();
		}
	case 1:
		if(role == Qt::DisplayRole)
		{
			switch(index.row())
			{
			case 0: return creature->getCiv();
			case 1: return creature->getNickname();
			case 2: return creature->getEnglishName();
			case 3: return creature->getSex();
			case 4: return creature->getDOB();
			case 5: return creature->getAge();		
			case 6: return creature->getRawCreature().custom_profession;
			case 8: return creature->x();
			case 9: return creature->y();
			case 10: return creature->z();
			default: return QVariant();
			}
		}
		else
			return QVariant();

	default:
		return QVariant();
	}
}

QVariant miscTableModel::headerData(int section,
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

Qt::ItemFlags miscTableModel::flags(const QModelIndex & index) const
{
	if (!index.isValid())
		return Qt::NoItemFlags;

	if(index.column() == 1)
	{
		switch(index.row())
		{
		case 0:
		case 3:
		case 8:
		case 9:
		case 10: return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
		default: return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
		}
	}
	else
		return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

bool miscTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if((index.column() == 1))
	{
		int32_t temp = value.toInt();

		switch(index.row())
		{
		case 0:
			creature->setCiv(temp);
			return true;

		case 3:
			creature->toggleSex();
			return true;

		case 8:
			if(temp > std::numeric_limits<uint16_t>::max())
				temp = std::numeric_limits<uint16_t>::max();
			creature->setX(temp);
			return true;

		case 9:
			if(temp > std::numeric_limits<uint16_t>::max())
				temp = std::numeric_limits<uint16_t>::max();
			creature->setY(temp);
			return true;

		case 10:
			if(temp > std::numeric_limits<uint16_t>::max())
				temp = std::numeric_limits<uint16_t>::max();
			creature->setZ(temp);
			return true;

		default: return false;
		}
	}	
	else
		return false;
}
