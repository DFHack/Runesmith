#include "RSCreature.h"
#include "rsException.h"
#include "DFInterface.h"

RSCreature::RSCreature(DFHack::t_creature nRawCreature, uint32_t nID, DFInterface *nDFI) :
	DFI(nDFI), rawCreature(nRawCreature), RSID(nID)
{
	if(!DFI)
		throw RSException();

	if(rawCreature.name.has_name)
	{
		englishName = rawCreature.name.first_name[0];
		englishName = englishName.toUpper();
		englishName += rawCreature.name.first_name+1;
		englishName += " ";
		englishName += DFI->translateName(rawCreature.name, true);

		dwarvishName = rawCreature.name.first_name[0];
		dwarvishName = dwarvishName.toUpper();
		dwarvishName += rawCreature.name.first_name+1;
		dwarvishName += " ";
		dwarvishName += DFI->translateName(rawCreature.name, false);
	}

	race = DFI->translateRace(rawCreature.race);
	profession = DFI->translateProfession(rawCreature.profession);
	age = QString::number(DFI->getCurrentYear() - rawCreature.birth_year);
	
	if((rawCreature.mood > -1) && (rawCreature.mood < 6))
	{
		moodSkill = DFI->translateSkill(rawCreature.mood_skill);
		mood = DFI->getMood(rawCreature.mood);
		DFI->readMats(&rawCreature, jobMats);

		for(unsigned int i=0; i<jobMats.size(); i++)
		{
			formattedMats.push_back(DFI->getMatDescription(jobMats[i]));
		}
	}
	else
	{
		mood = "None";
		moodSkill = " - ";
	}

	for(unsigned int i=0; i<NUM_TRAITS; i++)
	{
		cacheItem temp;
		temp.id = i;
		temp.text = DFI->translateTrait(i, rawCreature.defaultSoul.traits[i]);
				
		if(temp.text != "")
			traitCache.push_back(temp);
	}

	genSkillsCache();

	for(uint8_t i=0; i<NUM_CREATURE_LABORS; i++)
	{
		if(!rawCreature.labors[i])
			continue;

		cacheItem temp;
		temp.id = i;
		temp.text = DFI->translateLabour(i);

		//if(
		labourCache.push_back(temp);
	}
}

RSCreature::~RSCreature(void)
{
}

const uint32_t RSCreature::getID()
{
	return RSID;
}

const uint32_t RSCreature::getNumSkills()
{
	return rawCreature.defaultSoul.numSkills;
}

const uint32_t RSCreature::getHappiness()
{
	return rawCreature.happiness;
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
	return rawCreature.name.nickname;
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
	return QString::number(rawCreature.strength.level);
}

QString RSCreature::getAgility()
{
	return QString::number(rawCreature.agility.level);
}

QString RSCreature::getToughness()
{
	return QString::number(rawCreature.toughness.level);
}

QString RSCreature::getEndurance()
{
	return QString::number(rawCreature.endurance.level);
}

QString RSCreature::getRecuperation()
{
	return QString::number(rawCreature.recuperation.level);
}

QString RSCreature::getDiseaseRes()
{
	return QString::number(rawCreature.disease_resistance.level);
}

QString RSCreature::getWillpower()
{
	return QString::number(rawCreature.defaultSoul.willpower.level);
}

QString RSCreature::getMemory()
{
	return QString::number(rawCreature.defaultSoul.memory.level);
}

QString RSCreature::getFocus()
{
	return QString::number(rawCreature.defaultSoul.focus.level);
}

QString RSCreature::getIntuition()
{
	return QString::number(rawCreature.defaultSoul.intuition.level);
}

QString RSCreature::getPatience()
{
	return QString::number(rawCreature.defaultSoul.patience.level);
}

QString RSCreature::getEmpathy()
{
	return QString::number(rawCreature.defaultSoul.empathy.level);
}

QString RSCreature::getSocialAwareness()
{
	return QString::number(rawCreature.defaultSoul.social_awareness.level);
}

QString RSCreature::getCreativity()
{
	return QString::number(rawCreature.defaultSoul.creativity.level);
}

QString RSCreature::getMusicality()
{
	return QString::number(rawCreature.defaultSoul.musicality.level);
}

QString RSCreature::getAnalyticalAbility()
{
	return QString::number(rawCreature.defaultSoul.analytical_ability.level);
}

QString RSCreature::getLinguisticAbility()
{
	return QString::number(rawCreature.defaultSoul.linguistic_ability.level);
}

QString RSCreature::getSpatialSense()
{
	return QString::number(rawCreature.defaultSoul.spatial_sense.level);
}

QString RSCreature::getKinestheticSense()
{
	return QString::number(rawCreature.defaultSoul.kinesthetic_sense.level);
}

QString const& RSCreature::getAge()
{
	return age;
}

QString const& RSCreature::getRace()
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

QString const& RSCreature::getProfession()
{
	return profession;
}

std::vector<formattedSkill> const& RSCreature::getFormattedSkills()
{
	return skillsCache;
}

std::vector<cacheItem> const& RSCreature::getLabourCache()
{
	return labourCache;
}

std::vector<cacheItem> const& RSCreature::getTraitCache()
{
	return traitCache;
}

std::vector<QString> const& RSCreature::getJobMats()
{
	return formattedMats;
}

std::vector<DFHack::t_material> const& RSCreature::getRawMats()
{
	return jobMats;
}

DFHack::t_creaturflags1 & RSCreature::getFlags1()
{
	return rawCreature.flags1;
}

DFHack::t_creaturflags2 & RSCreature::getFlags2()
{
	return rawCreature.flags2;
}

const int32_t RSCreature::getCiv()
{
	return rawCreature.civ;
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

DFHack::t_creature const& RSCreature::getRawCreature()
{
	return rawCreature;
}

statusTracker const& RSCreature::getChanged()
{
	return dataChanged;
}

bool RSCreature::isChanged()
{
	if(dataChanged.skillsChanged)
		return true;

	if(dataChanged.attributesChanged)
		return true;

	if(dataChanged.flagsChanged)
		return true;

	if(dataChanged.happinessChanged)
		return true;

	if(dataChanged.sexChanged)
		return true;

	if(dataChanged.traitsChanged)
		return true;

	if(dataChanged.moodChanged)
		return true;

	if(dataChanged.posChanged)
		return true;

	if(dataChanged.civChanged)
		return true;

	return false;
}

void RSCreature::toggleSex()
{
	rawCreature.sex = !rawCreature.sex;
	dataChanged.sexChanged = true;
}

void RSCreature::setCiv(int32_t nCiv)
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
	}
	else
	{
		if(!rawCreature.flags1.bits.has_mood)
			rawCreature.flags1.bits.has_mood = 1;
	}

	mood = DFI->getMood(rawCreature.mood);
	dataChanged.moodChanged = true;
	dataChanged.flagsChanged = true;
}

void RSCreature::setMoodSkill(uint8_t skill)
{
	rawCreature.mood_skill = rawCreature.defaultSoul.skills[skill].id;
	moodSkill = DFI->translateSkill(rawCreature.mood_skill);
	dataChanged.moodChanged = true;
}

void RSCreature::setFlagsChanged()
{
	dataChanged.flagsChanged = true;
}

void RSCreature::setHappiness(uint32_t hapVal)
{
	rawCreature.happiness = hapVal;
	dataChanged.happinessChanged = true;
}

void RSCreature::setAllSkillLevels(uint8_t nLevel)
{
	uint32_t numSkills = rawCreature.defaultSoul.numSkills;

	for(int i=0; i<numSkills; i++)
	{
		rawCreature.defaultSoul.skills[i].rating = nLevel;
	}

	genSkillsCache();
	dataChanged.skillsChanged = true;
}

void RSCreature::setSkillLevel(uint8_t id, uint8_t nLevel)
{
	rawCreature.defaultSoul.skills[id].rating = nLevel;
	updateSkillsCache(id);
	dataChanged.skillsChanged = true;
}

void RSCreature::setSkillExperiance(uint8_t id, uint16_t nExp)
{
	rawCreature.defaultSoul.skills[id].experience = nExp;
	updateSkillsCache(id);
	dataChanged.skillsChanged = true;
}

bool RSCreature::editTrait(uint32_t id, uint32_t level)
{
	if(!DFI)
		return false;

	switch(level)
	{
	case 0: rawCreature.defaultSoul.traits[id] = 9; break;
	case 1: rawCreature.defaultSoul.traits[id] = 24; break;
	case 2: rawCreature.defaultSoul.traits[id] = 60; break;
	case 3: rawCreature.defaultSoul.traits[id] = 75; break;
	case 4: rawCreature.defaultSoul.traits[id] = 90; break;
	case 5: rawCreature.defaultSoul.traits[id] = 100; break;
	default: return false;
	}

	dataChanged.traitsChanged = true;
	cacheItem temp;
	temp.id = id;
	temp.text = DFI->translateTrait(id, rawCreature.defaultSoul.traits[id]);
	traitCache.push_back(temp);
	return true;
}

bool RSCreature::addTrait(uint32_t id, uint32_t level)
{	
	if(!DFI)
		return false;

	switch(level)
	{
	case 0: rawCreature.defaultSoul.traits[id] = 9; break;
	case 1: rawCreature.defaultSoul.traits[id] = 24; break;
	case 2: rawCreature.defaultSoul.traits[id] = 60; break;
	case 3: rawCreature.defaultSoul.traits[id] = 75; break;
	case 4: rawCreature.defaultSoul.traits[id] = 90; break;
	case 5: rawCreature.defaultSoul.traits[id] = 100; break;
	default: return false;
	}

	dataChanged.traitsChanged = true;
	cacheItem temp;
	temp.id = id;
	temp.text = DFI->translateTrait(id, rawCreature.defaultSoul.traits[id]);
	traitCache.push_back(temp);
	return true;
}

void RSCreature::setAllAttributes(uint16_t nVal)
{
	rawCreature.strength.level = nVal;
	rawCreature.agility.level = nVal;
	rawCreature.toughness.level = nVal;
	rawCreature.endurance.level = nVal;
	rawCreature.recuperation.level = nVal;
	rawCreature.disease_resistance.level = nVal;
	rawCreature.defaultSoul.willpower.level = nVal;
	rawCreature.defaultSoul.memory.level = nVal;
	rawCreature.defaultSoul.focus.level = nVal;
	rawCreature.defaultSoul.intuition.level = nVal;
	rawCreature.defaultSoul.patience.level = nVal;
	rawCreature.defaultSoul.empathy.level = nVal;
	rawCreature.defaultSoul.social_awareness.level = nVal;
	rawCreature.defaultSoul.creativity.level = nVal;
	rawCreature.defaultSoul.musicality.level = nVal;
	rawCreature.defaultSoul.analytical_ability.level = nVal;
	rawCreature.defaultSoul.linguistic_ability.level = nVal;
	rawCreature.defaultSoul.spatial_sense.level = nVal;
	rawCreature.defaultSoul.kinesthetic_sense.level = nVal;	
	dataChanged.attributesChanged = true;
}

void RSCreature::setStrength(uint32_t nVal)
{
	rawCreature.strength.level = nVal;
	dataChanged.attributesChanged = true;
}

void RSCreature::setAgility(uint32_t nVal)
{
	rawCreature.agility.level = nVal;
	dataChanged.attributesChanged = true;
}

void RSCreature::setToughness(uint32_t nVal)
{
	rawCreature.toughness.level = nVal;
	dataChanged.attributesChanged = true;
}

void RSCreature::setEndurance(uint32_t nVal)
{
	rawCreature.endurance.level = nVal;
	dataChanged.attributesChanged = true;
}

void RSCreature::setRecuperation(uint32_t nVal)
{
	rawCreature.recuperation.level = nVal;
	dataChanged.attributesChanged = true;
}

void RSCreature::setDiseaseRes(uint32_t nVal)
{
	rawCreature.disease_resistance.level = nVal;
	dataChanged.attributesChanged = true;
}

void RSCreature::setWillpower(uint32_t nVal)
{
	rawCreature.defaultSoul.willpower.level = nVal;
	dataChanged.attributesChanged = true;
}

void RSCreature::setMemory(uint32_t nVal)
{
	rawCreature.defaultSoul.memory.level = nVal;
	dataChanged.attributesChanged = true;
}

void RSCreature::setFocus(uint32_t nVal)
{
	rawCreature.defaultSoul.focus.level = nVal;
	dataChanged.attributesChanged = true;
}

void RSCreature::setIntuition(uint32_t nVal)
{
	rawCreature.defaultSoul.intuition.level = nVal;
	dataChanged.attributesChanged = true;
}

void RSCreature::setPatience(uint32_t nVal)
{
	rawCreature.defaultSoul.patience.level = nVal;
	dataChanged.attributesChanged = true;
}

void RSCreature::setEmpathy(uint32_t nVal)
{
	rawCreature.defaultSoul.empathy.level = nVal;
	dataChanged.attributesChanged = true;
}

void RSCreature::setSocialAwareness(uint32_t nVal)
{
	rawCreature.defaultSoul.social_awareness.level = nVal;
	dataChanged.attributesChanged = true;
}

void RSCreature::setCreativity(uint32_t nVal)
{
	rawCreature.defaultSoul.creativity.level = nVal;
	dataChanged.attributesChanged = true;
}

void RSCreature::setMusicality(uint32_t nVal)
{
	rawCreature.defaultSoul.musicality.level = nVal;
	dataChanged.attributesChanged = true;
}

void RSCreature::setAnalyticalAbility(uint32_t nVal)
{
	rawCreature.defaultSoul.analytical_ability.level = nVal;
	dataChanged.attributesChanged = true;
}

void RSCreature::setLinguisticAbility(uint32_t nVal)
{
	rawCreature.defaultSoul.linguistic_ability.level = nVal;
	dataChanged.attributesChanged = true;
}

void RSCreature::setSpatialSense(uint32_t nVal)
{
	rawCreature.defaultSoul.spatial_sense.level = nVal;
	dataChanged.attributesChanged = true;
}

void RSCreature::setKinestheticSense(uint32_t nVal)
{
	rawCreature.defaultSoul.kinesthetic_sense.level = nVal;
	dataChanged.attributesChanged = true;
}

void RSCreature::resetFlags()
{
	dataChanged.skillsChanged = false;
	dataChanged.attributesChanged = false;
	dataChanged.flagsChanged = false;
	dataChanged.happinessChanged = false;
	dataChanged.sexChanged = false;
	dataChanged.traitsChanged = false;
	dataChanged.moodChanged = false;
	dataChanged.posChanged = false;
	dataChanged.civChanged = false;
}

void RSCreature::genSkillsCache()
{
	for(unsigned int i=0; i<rawCreature.defaultSoul.numSkills; i++)
	{
		formattedSkill temp;
		temp.id = i;
		temp.skill = DFI->translateSkill(rawCreature.defaultSoul.skills[i].id);
		temp.level = DFI->getLevelInfo(
			rawCreature.defaultSoul.skills[i].rating).name.c_str();

		temp.level.append(" [");
		temp.level.append(QString::number(
			rawCreature.defaultSoul.skills[i].rating));

		temp.level.append("]");
		temp.xp = rawCreature.defaultSoul.skills[i].experience;
		skillsCache.push_back(temp);
	}
}

void RSCreature::updateSkillsCache(uint8_t id)
{
	formattedSkill* item;

	if(skillsCache[id].id == id)
	{
		item = &skillsCache[id];
	}
	else
	{
		//slow but shouldn't usually hit here
		int len = skillsCache.size();

		for(int i=0; i<len; i++)
		{
			if(skillsCache[i].id = id)
				item = &skillsCache[i];
		}
	}

	item->level = DFI->getLevelInfo(
		rawCreature.defaultSoul.skills[id].rating).name.c_str();

	item->level.append(" [");
	item->level.append(QString::number(
		rawCreature.defaultSoul.skills[id].rating));

	item->level.append("]");
	item->skill = DFI->translateSkill(rawCreature.defaultSoul.skills[id].id);
	item->xp = rawCreature.defaultSoul.skills[id].experience;
}

void RSCreature::updateMoodCache()
{
	moodSkill = DFI->translateSkill(rawCreature.mood_skill);
	mood = DFI->getMood(rawCreature.mood);
	formattedMats.clear();

	for(unsigned int i=0; i<jobMats.size(); i++)
	{
		formattedMats.push_back(DFI->getMatDescription(jobMats[i]));
	}
}

void RSCreature::kill()
{
	rawCreature.flags1.bits.dead = 1;
}

void RSCreature::setMat(uint32_t id, int32_t nIndex, const char* text, int16_t subIndex)
{
	if(id < jobMats.size())
	{
		jobMats[id].index = nIndex;
		formattedMats[id] = text;
		dataChanged.moodChanged = true;

		if(subIndex >= 0)
			jobMats[id].subIndex = subIndex;
	}
}
