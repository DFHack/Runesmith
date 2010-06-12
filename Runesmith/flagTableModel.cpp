#include "flagTableModel.h"

flagTableModel::flagTableModel(QObject *parent) : skillsTableModel(parent, 1)
{
}

flagTableModel::~flagTableModel(void)
{
}

int flagTableModel::rowCount(const QModelIndex &parent) const
{
	if(creature)
	{
		return NUM_FLAGS_SHOWN;
	}
	else
		return 0;
}

QVariant flagTableModel::data(const QModelIndex &index, int role) const
{
	if((!creature) || (!DFI))
		return QVariant();	

	switch(index.column())
	{
	case 0:
		if(role == Qt::DisplayRole)
		{
			switch(index.row())
			{
			case 0: return "Test";
			default: return QVariant();
			}
		}
		else if(role == Qt::CheckStateRole)
		{
			switch(index.row())
			{
			case 0: return Qt::Checked;
			default: return Qt::Unchecked;
			}
		}
		else
			return QVariant();
		
	default:
		return QVariant();
	}
}

QVariant flagTableModel::headerData(int section,
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
			return QString("Flags");	

		default:
			return QVariant();
		}
	}
	else
		return QVariant();
}

Qt::ItemFlags flagTableModel::flags(const QModelIndex & index) const
{
	if (!index.isValid())
		return Qt::ItemFlag::NoItemFlags;

	//if (index.column() == 0)
	//{
		return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemFlag::ItemIsUserCheckable;
	//}
	//else
	//	return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

bool flagTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	return false;
}
