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

	DFHack::t_creature const& rawCre = creature->getRawCreature();

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
		case 11: return QString("Empathy");
		case 12: return QString("Social Awareness");
		case 13: return QString("Creatvity");
		case 14: return QString("Musicality");
		case 15: return QString("Analytical Ability");
		case 16: return QString("Linguistic Ability");
		case 17: return QString("Spatial Sense");
		case 18: return QString("Kinaesthetic Sense");		
		default: return QVariant();
		}

	case 1:
		switch(index.row())
		{
		case 0: return creature->getStrength();
		case 1: return creature->getAgility();
		case 2: return creature->getToughness();
		case 3: return creature->getEndurance();
		case 4: return creature->getRecuperation();
		case 5: return creature->getDiseaseRes();
		case 6: return creature->getWillpower();
		case 7: return creature->getMemory();
		case 8: return creature->getFocus();
		case 9: return creature->getIntuition();
		case 10: return creature->getPatience();
		case 11: return creature->getEmpathy();
		case 12: return creature->getSocialAwareness();
		case 13: return creature->getCreativity();
		case 14: return creature->getMusicality();
		case 15: return creature->getAnalyticalAbility();
		case 16: return creature->getLinguisticAbility();
		case 17: return creature->getSpatialSense();
		case 18: return creature->getKinestheticSense();
		default: return QVariant();
		}

	case 2:
		switch(index.row())
		{
		case 0: return QString(QString::number(DFI->getRacialAverage(rawCre.race, rawCre.caste, STRENGTH_STAT)));
		case 1: return QString(QString::number(DFI->getRacialAverage(rawCre.race, rawCre.caste, AGILITY_STAT)));
		case 2: return QString(QString::number(DFI->getRacialAverage(rawCre.race, rawCre.caste, TOUGHNESS_STAT)));
		case 3: return QString(QString::number(DFI->getRacialAverage(rawCre.race, rawCre.caste, ENDURANCE_STAT)));
		case 4: return QString(QString::number(DFI->getRacialAverage(rawCre.race, rawCre.caste, RECUPERATION_STAT)));
		case 5: return QString(QString::number(DFI->getRacialAverage(rawCre.race, rawCre.caste, DISEASE_RESISTANCE_STAT)));
		case 6: return QString(QString::number(DFI->getRacialAverage(rawCre.race, rawCre.caste, WILLPOWER_STAT)));
		case 7: return QString(QString::number(DFI->getRacialAverage(rawCre.race, rawCre.caste, MEMORY_STAT)));
		case 8: return QString(QString::number(DFI->getRacialAverage(rawCre.race, rawCre.caste, FOCUS_STAT)));
		case 9: return QString(QString::number(DFI->getRacialAverage(rawCre.race, rawCre.caste, INTUITION_STAT)));
		case 10: return QString(QString::number(DFI->getRacialAverage(rawCre.race, rawCre.caste, PATIENCE_STAT)));
		case 11: return QString("-");//QString::number(DFI->getRacialAverage(rawCre.race, rawCre.caste, EMPATHY_STAT)));
		case 12: return QString("-");//QString::number(DFI->getRacialAverage(rawCre.race, rawCre.caste, SOCIAL_AWARENESS_STAT)));
		case 13: return QString(QString::number(DFI->getRacialAverage(rawCre.race, rawCre.caste, CREATVITY_STAT)));
		case 14: return QString(QString::number(DFI->getRacialAverage(rawCre.race, rawCre.caste, MUSICALITY_STAT)));
		case 15: return QString(QString::number(DFI->getRacialAverage(rawCre.race, rawCre.caste, ANALYTICAL_ABILITY_STAT)));
		case 16: return QString(QString::number(DFI->getRacialAverage(rawCre.race, rawCre.caste, LINGUISTIC_ABILITY_STAT)));
		case 17: return QString(QString::number(DFI->getRacialAverage(rawCre.race, rawCre.caste, SPATIAL_SENSE_STAT)));
		case 18: return QString(QString::number(DFI->getRacialAverage(rawCre.race, rawCre.caste, KINESTHETIC_SENSE_STAT)));		
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

		case 2:
			return QString("Racial Average");

		default:
			return QVariant();
		}
	}
	else
		return QVariant();
}

bool attrTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if(!DFI)
		return false;

	if(!DFI->isAttached())
		return false;

	uint32_t temp = value.toUInt();	

	switch(index.row())
	{
	case 0: creature->setStrength(temp); break;
	case 1: creature->setAgility(temp); break;
	case 2: creature->setToughness(temp); break;
	case 3: creature->setEndurance(temp); break;
	case 4: creature->setRecuperation(temp); break;
	case 5: creature->setDiseaseRes(temp); break;
	case 6: creature->setWillpower(temp); break;
	case 7: creature->setMemory(temp); break;
	case 8: creature->setFocus(temp); break;
	case 9: creature->setIntuition(temp); break;
	case 10: creature->setPatience(temp); break;
	case 11: creature->setEmpathy(temp); break;
	case 12: creature->setSocialAwareness(temp); break;
	case 13: creature->setCreativity(temp); break;
	case 14: creature->setMusicality(temp); break;
	case 15: creature->setAnalyticalAbility(temp); break;
	case 16: creature->setLinguisticAbility(temp); break;
	case 17: creature->setSpatialSense(temp); break;
	case 18: creature->setKinestheticSense(temp); break;		
	default: return false;
	}

	return true;
}

Qt::ItemFlags attrTableModel::flags(const QModelIndex & index) const
{
	if (!index.isValid())
		return Qt::NoItemFlags;

	if(index.column() == 1)
	{
		return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
	}
	else
		return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}
