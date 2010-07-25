#include "RSCreature.h"

RSCreature::RSCreature(void)
{
}

RSCreature::~RSCreature(void)
{
}

QString RSCreature::getDOB()
{
	QString temp = QString::number((rawCreature.birth_time/1200) % 28 + 1);
	temp.append("/");
	temp.append(QString::number(rawCreature.birth_time/1200/28));
	temp.append("/");
	temp.append(QString::number(rawCreature.birth_year));
	return temp;
}

QString RSCreature::getSex()
{
	return rawCreature.sex ? "Male" : "Female";
}

QString RSCreature::getStatus()
{
	QString temp;

	if(rawCreature.flags1.bits.dead)
		return "Dead";
	
	if(rawCreature.mood >= 0)
	{
		temp = "( ";
		temp.append(DFI->getMood(rawCreature.mood));
		temp.append(" ) ");
	}

	if(rawCreature.flags1.bits.drowning)
		temp.append("( Drowning ) ");

	if(rawCreature.flags2.bits.for_trade)
		temp.append("( For Trade ) ");

	if(rawCreature.flags2.bits.slaughter)
		temp.append("( For Slaughter ) ");

	if(rawCreature.flags2.bits.breathing_problem)
		temp.append("( Breathing Problem ) ");

	if(rawCreature.flags2.bits.vision_damaged)
		temp.append("( Vision Damaged ) ");

	if(rawCreature.flags2.bits.vision_missing)
		temp.append("( Vision Missing ) ");

	if(rawCreature.flags1.bits.chained)
		temp.append("( Chanined ) ");

	if(rawCreature.flags1.bits.caged)
		temp.append("( Caged ) ");

	if(rawCreature.flags1.bits.invades)
		temp.append("( Invading ) ");

	if(rawCreature.flags1.bits.hidden_in_ambush)
		temp.append("( Hidden in Ambush ) ");

	if(rawCreature.flags2.bits.sparring)
		temp.append("( Sparring ) ");

	if(rawCreature.flags2.bits.swimming)
		temp.append("( Swimming ) ");

	if(rawCreature.flags2.bits.visitor || 
		rawCreature.flags2.bits.visitor_uninvited)
		temp.append("( Visitor ) ");

	return temp;
}

QString RSCreature::getNickname()
{
	rawCreature.name.nickname;
}

QString RSCreature::getFormattedHappiness()
{
	QString temp;

	if (rawCreature.happiness < 1)
		temp = "Miserable";
	else if (rawCreature.happiness <= 25)
		temp = "Very Unhappy";
	else if (rawCreature.happiness <= 50)
		temp = "Unhappy";
	else if (rawCreature.happiness <= 75)
		temp = "Fine";
	else if (rawCreature.happiness <= 125)
		temp = "Content";
	else if (rawCreature.happiness <= 150)
		temp = "Happy";
	else
		temp = "Ecstatic";

	temp.append(" [");
	temp.append(QString::number(rawCreature.happiness));
	return temp.append("]");
}

QString RSCreature::getStrength()
{
	return rawCreature.strength;
}

QString RSCreature::getAgility()
{
	return rawCreature.agility;
}

QString RSCreature::getToughness()
{
	return rawCreature.toughness;
}

QString RSCreature::getEndurance()
{
	return rawCreature.endurance;
}

QString RSCreature::getRecuperation()
{
	return rawCreature.recuperation;
}

QString RSCreature::getDiseaseRes()
{
	return rawCreature.disease_resistance;
}

QString RSCreature::getWillpower()
{
	return rawCreature.defaultSoul.willpower;
}

QString RSCreature::getMemory()
{
	return rawCreature.defaultSoul.memory;
}

QString RSCreature::getFocus()
{
	return rawCreature.defaultSoul.focus;
}

QString RSCreature::getIntuition()
{
	return rawCreature.defaultSoul.intuition;
}

QString RSCreature::getPatience()
{
	return rawCreature.defaultSoul.patience;
}

QString RSCreature::getEmpathy()
{
	return rawCreature.defaultSoul.empathy;
}

QString RSCreature::getSocialAwareness()
{
	return rawCreature.defaultSoul.social_awareness;
}

QString RSCreature::getCreativity()
{
	return rawCreature.defaultSoul.creativity;
}

QString RSCreature::getMusicality()
{
	return rawCreature.defaultSoul.musicality;
}

QString RSCreature::getAnalyticalAbility()
{
	return rawCreature.defaultSoul.analytical_ability;
}

QString RSCreature::getLinguisticAbility()
{
	return rawCreature.defaultSoul.linguistic_ability;
}

QString RSCreature::getSpatialSense()
{
	return rawCreature.defaultSoul.spatial_sense;
}

QString RSCreature::getKinestheticSense()
{
	return rawCreature.defaultSoul.kinesthetic_sense;
}

QString const& RSCreature::getAge()
{
	return age;
}

QString const& RSCreature::getRace();
{
	return race;
}

QString const& RSCreature::getMood()
{
	return mood;
}

QString const& RSCreature::getEnglishName()
{
	return englishName;
}

QString const& RSCreature::getDwarvishName()
{
	return dwarvishName;
}

QString const& RSCreature::getMoodSkill()
{
	return moodSkill;
}

std::vector<QString> const& RSCreature::getFormattedSkills()
{
	return formattedSkills;
}

std::vector<QString> const& RSCreature::getLabourCache()
{
	return labourCache;
}

std::vector<QString> const& RSCreature::getTraitCache()
{
	return traitCache;
}

std::vector<QString> const& RSCreature::getJobMats()
{
	return formattedMats;
}

DFHack::t_creaturflags1 & RSCreature::getFlags1()
{
	return rawCreature.flags1;
}

DFHack::t_creaturflags1 & RSCreature::getFlags2()
{
	return rawCreature.flags2;
}

bool RSCreature::isPlayerCiv()
{
	return (creature->civ == -1) ? false : true;
}

uint16_t RSCreature::x()
{
	return rawCreature.x;
}

uint16_t RSCreature::y()
{
	return rawCreature.y;
}

uint16_t RSCreature::z()
{
	return rawCreature.z;
}

void RSCreature::toggleSex()
{
	rawCreature.sex != rawCreature.sex;
	dataChanged.sexChanged = true;
}

void RSCreature::setCiv(int nCiv)
{
	rawCreature.civ = nCiv;
	dataChanged.civChanged = true;
}

void RSCreature::setX(uint16_t nVal)
{
	rawCreature.x = nVal;
	dataChanged.posChanged = true;
}

void RSCreature::setY(uint16_t nVal)
{
	rawCreature.y = nVal;
	dataChanged.posChanged = true;
}

void RSCreature::setZ(uint16_t nVal)
{
	rawCreature.z = nVal;
	dataChanged.posChanged = true;
}

void RSCreature::setMood(int nMood)
{
	rawCreature.mood = nMood;

	if(nMood == -1)
	{
		if(rawCreature.flags1.bits.has_mood)
			rawCreature.flags1.bits.has_mood = 0;
		dataChanged.flagsChanged = true;
	}
	else
	{
		if(!rawCreature.flags1.bits.has_mood)
			rawCreature.flags1.bits.has_mood = 1;
		
		dataChanged.flagsChanged = true;
	}
}

void RSCreature::setFlagsChanged()
{
	dataChanged.flagsChanged = true;
}

void RSCreature::setHappiness(uint32_t hapVal);
{
	rawCreature.happiness = hapVal;
	dataChanged.happinessChanged = true;
}

void RSCreature::setSkillLevel(uint8_t nLevel)
{
}

void RSCreature::setSkillExperiance(uint16_t nExp)
{
}

void RSCreature::addTrait(uint32_t id, uint32_t level)
{
}

void RSCreature::editTrait(uint32_t id, uint32_t level)
{
}

void RSCreature::setRawCreature(DFHack::t_creature nRawCreature)
{
}

void RSCreature::setStrength(uint32_t nVal)
{
}

void RSCreature::setAgility(uint32_t nVal)
{
}

void RSCreature::setToughness(uint32_t nVal)
{
}

void RSCreature::setEndurance(uint32_t nVal)
{
}

void RSCreature::setRecuperation(uint32_t nVal)
{
}

void RSCreature::setDiseaseRes(uint32_t nVal)
{
}

void RSCreature::setWillpower(uint32_t nVal)
{
}

void RSCreature::setMemory(uint32_t nVal)
{
}

void RSCreature::setFocus(uint32_t nVal)
{
}

void RSCreature::setIntuition(uint32_t nVal)
{
}

void RSCreature::setPatience(uint32_t nVal)
{
}

void RSCreature::setEmpathy(uint32_t nVal)
{
}

void RSCreature::setSocialAwareness(uint32_t nVal)
{
}

void RSCreature::setCreativity(uint32_t nVal)
{
}

void RSCreature::setMusicality(uint32_t nVal)
{
}

void RSCreature::setAnalyticalAbility(uint32_t nVal)
{
}

void RSCreature::setLinguisticAbility(uint32_t nVal)
{
}

void RSCreature::setSpatialSense(uint32_t nVal)
{
}

void RSCreature::setKinestheticSense(uint32_t nVal)
{
}

void RSCreature::resetFlags()
{
	skillsChanged = false;
	attributesChanged = false;
	flagsChanged = false;
	happinessChanged = false;
	sexChanged = false;
	traitsChanged = false;
	moodChanged = false;
	posChanged = false;
	civChanged = false;
}