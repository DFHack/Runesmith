#include <string>
#include <QColor>
#include "dwarfTableModel.h"

dwarfTableModel::dwarfTableModel(QObject *parent, int nColCount) 
	: QAbstractTableModel(parent), colCount(nColCount), DFI(NULL)
{	
}

dwarfTableModel::~dwarfTableModel(void)
{
}

int dwarfTableModel::rowCount(const QModelIndex &parent) const
{
	if(!DFI)
		return 0;

	std::vector<DFHack::t_creature>& dwarves = DFI->getDwarves();
	return dwarves.size();
}

int dwarfTableModel::columnCount(const QModelIndex &parent) const
{
	return colCount;
}

QVariant dwarfTableModel::data(const QModelIndex &index, int role) const
{
	if(!DFI)
		return QVariant();

	if(!DFI->isAttached())
		return QVariant();
	
	std::vector<DFHack::t_creature>& dwarves = DFI->getDwarves();	

	if(index.row() >= dwarves.size())
		return QVariant();
	
	QString transName;
	//RS_HappinessState hapState = calcHappinessState();

	if(role == Qt::DisplayRole)
	{
		switch(index.column())
		{
		case 0:		
			transName = dwarves[index.row()].name.first_name;
			transName.append(" ");
			transName.append(DFI->translateName(dwarves[index.row()].name));
			return transName;

		case 1:
			return QString(DFI->translateProfession(dwarves[index.row()].profession));

		case 2:
			if (dwarves[index.row()].happiness < 1)
				transName = "Miserable";
			else if (dwarves[index.row()].happiness <= 25)
				transName = "Very Unhappy";
			else if (dwarves[index.row()].happiness <= 50)
				transName = "Unhappy";
			else if (dwarves[index.row()].happiness <= 75)
				transName = "Fine";
			else if (dwarves[index.row()].happiness <= 125)
				transName = "Content";
			else if (dwarves[index.row()].happiness <= 150)
				transName = "Happy";
			else
				transName = "Ecstatic";
			transName.append(" [");
			transName.append(QString::number(dwarves[index.row()].happiness));
			return transName.append("]");

		case 3:
			//TODO make this general status instead of just mood
			switch(dwarves[index.row()].mood)
			{
			case -1: return QVariant();
			case 0: return QString("Fey");
			case 1: return QString("Possesed");
			case 2:
			case 3:
			case 4: return QVariant();
			case 5:	return QString("Melancholy/Beserk");
			}		
			 
		default:
			return QVariant();
		}
	}
	else if((role == Qt::BackgroundColorRole) && (index.column() == 2))
	{
		int green = dwarves[index.row()].happiness + HAPPINESS_WEIGHT;
		if(green > 255)
			green = 255;		
		return QColor(255-green, green, 0);
	}
	else
		return QVariant();
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

		default:
			return QVariant();
		}
	}
	else
		return QVariant();
}

void dwarfTableModel::update(DFInterface *nDFI)
{
	DFI = nDFI;
	reset();
	emit dataChanged(QAbstractItemModel::createIndex(0, 0), 
		QAbstractItemModel::createIndex(colCount, rowCount()));
}
