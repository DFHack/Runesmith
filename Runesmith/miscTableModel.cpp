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
		return 10;
	}
	else
		return 0;
}

QVariant miscTableModel::data(const QModelIndex &index, int role) const
{
	if((!creature) || (!DFI) || (role != Qt::DisplayRole))
		return QVariant();

	switch(index.column())
	{
	case 0:
		switch(index.row())
		{
		case 0:	return QString("Nickname:");	
		case 1:	return QString("English Name:");
		case 2:	return QString("Sex:");
		case 3:	return QString("DOB (D/M/Y):");
		case 4:	return QString("Age:");
		case 5:	return QString("Custom Profession:");
		case 6: return QString("Position:");
		case 7: return QString("X");
		case 8: return QString("Y");
		case 9: return QString("Z");
		default: return QVariant();
		}
	case 1:
		switch(index.row())
		{
		case 0: return creature->name.nickname;
		case 1: return DFI->translateName(creature->name, true);
		case 2: return creature->sex ? "Male" : "Female";
		case 3: return calcDob();
		case 4: return (DFI->getCurrentYear() - creature->birth_year);
		case 5: return creature->custom_profession;
		case 7: return creature->x;
		case 8: return creature->y;
		case 9: return creature->z;
		default: return QVariant();
		}

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
		return Qt::ItemFlag::NoItemFlags;

	if((index.column() == 1) && (index.row() == 2))
	{
		return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemFlag::ItemIsEditable;
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

	if((index.column() == 1) && (index.row() == 2))
	{
		int temp = value.toInt();
		creature->sex = temp;
		DFI->setChanged(creature->id, SEX_CHANGED);
		return true;
	}	
	else
		return false;
}
