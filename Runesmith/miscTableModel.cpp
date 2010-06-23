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
	if((!creature) || (!DFI))
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
			case 0: return (creature->civ == -1) ? "False" : "True";
			case 1: return creature->name.nickname;
			case 2: return DFI->translateName(creature->name, true);
			case 3: return creature->sex ? "Male" : "Female";
			case 4: return calcDob();
			case 5: return (DFI->getCurrentYear() - creature->birth_year);		
			case 6: return creature->custom_profession;
			case 8: return creature->x;
			case 9: return creature->y;
			case 10: return creature->z;
			default: return QVariant();
			}
		}
		else if(role == Qt::CheckStateRole)
		{
			if(!index.row())
				return (creature->civ == -1) ? Qt::Unchecked : Qt::Checked;
			else
				return QVariant();
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

QString miscTableModel::calcDob() const
{
	QString temp = QString::number((creature->birth_time/1200) % 28 + 1);
	temp.append("/");
	temp.append(QString::number(creature->birth_time/1200/28));
	temp.append("/");
	temp.append(QString::number(creature->birth_year));
	return temp;
}

Qt::ItemFlags miscTableModel::flags(const QModelIndex & index) const
{
	if (!index.isValid())
		return Qt::NoItemFlags;

	if(index.column() == 1)
	{
		switch(index.row())
		{
		case 0: return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable;
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
	if(!DFI)
		return false;

	if(!DFI->isAttached())
		return false;

	if((index.column() == 1))
	{
		unsigned int temp = value.toUInt();

		if(temp > std::numeric_limits<uint16_t>::max())
			temp = std::numeric_limits<uint16_t>::max();

		switch(index.row())
		{
		case 0:
			if(creature->civ == -1)
				creature->civ = DFI->getDwarfCiv();
			else
				creature->civ = -1;

			DFI->setChanged(creature->id, CIV_CHANGED);
			return true;

		case 3:
			creature->sex = temp;
			DFI->setChanged(creature->id, SEX_CHANGED);
			return true;

		case 8:
			creature->x = temp;
			DFI->setChanged(creature->id, POS_CHANGED);
			return true;

		case 9:
			creature->y = temp;
			DFI->setChanged(creature->id, POS_CHANGED);
			return true;

		case 10:
			creature->z = temp;
			DFI->setChanged(creature->id, POS_CHANGED);
			return true;

		default: return false;
		}
	}	
	else
		return false;
}
