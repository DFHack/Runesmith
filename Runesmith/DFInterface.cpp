#include <algorithm>
#include "DFInterface.h"
#include "rsException.h"
#include "creatureCmps.h"
#include "RSCreature.h"

DFInterface::DFInterface(void) : DF(NULL), DFMgr(NULL), Materials(NULL), Tran(NULL),
	Creatures(NULL), mem(NULL), processDead(false), numCreatures(0), suspended(false)
{
	mainRace = "DWARF";

	try
	{
		DFMgr = new DFHack::ContextManager("Memory.xml");   
	}
	catch (std::exception& e)
	{
		throw;
	}
}

DFInterface::~DFInterface(void)
{
	detatch();
	cleanup();	
}

bool DFInterface::isAttached()
{
	if(DF)
	{
		try
		{
			return DF->isAttached();
		}
		catch(std::exception &e)
		{
			return false;
		}
	}
	else
		return false;
}

bool DFInterface::isContextValid()
{
	if(!DF)
		return false;

	DFHack::BadContexts inval;
	DFMgr->Refresh(&inval);
	
	if(inval.Contains(DF))
	{
		DF = NULL;
		return false;
	}
	else
		return true;
}

bool DFInterface::attach()
{
	if(!isAttached())
	{
		try
		{
			DF = DFMgr->getSingleContext(); 
		}
		catch (std::exception& e)
		{
			throw;
		}
	}

	if(isContextValid())
	{
		try
		{
			DF->Attach();
		}
		catch (std::exception& e)
		{
			throw;
		}	

		mem = DF->getMemoryInfo();
		Creatures = DF->getCreatures();
		Materials = DF->getMaterials();
		Tran = DF->getTranslation();
		world = DF->getWorld();
		suspend();	
		process();
		resume();
	}
}

void DFInterface::detatch()
{
	if(isContextValid())
	{
		if(isAttached())
		{				
			suspend();
			DF->Detach();
			numCreatures = 0;
			cleanup();
		}
	}
}

void DFInterface::forceResume()
{
	if(isContextValid())
	{
		if(isAttached())
		{
			try
			{
				DF->ForceResume();
			}
			catch(std::exception &e)
			{
				throw;
			}
		}
	}
}

void DFInterface::update()
{
	if(isContextValid())
	{
		if(isAttached())
		{
			suspend();			
			process();
			resume();
		}
	}
	else
	{
		numCreatures = 0;
		cleanup();
	}
}

std::vector<RSCreature*>& DFInterface::getDwarves()
{
	if(isAttached())
		if(!processDead)
			return dwarves;
		else
			return allDwarves;
	else
	{
		cleanup();
		return dwarves;
	}
}

std::vector<RSCreature*>& DFInterface::getCreatures()
{
	if(isAttached())
		if(!processDead)
			return creatures;
		else
			return allCreatures;
	else
	{
		cleanup();
		return creatures;
	}
}

RSCreature* DFInterface::getDwarf(uint32_t dwarf)
{
	if(isAttached())
		if(!processDead)
			return dwarves[dwarf];
		else
			return allDwarves[dwarf];
	else
		return NULL;
}

RSCreature* DFInterface::getCreature(uint32_t creature)
{
	if(isAttached())
		if(!processDead)
			return creatures[creature];
		else
			return allCreatures[creature];
	else	
		return NULL;
}

void DFInterface::resume()
{
	if(Creatures)
		Creatures->Finish();

	DF->Resume();
	suspended = false;
}

void DFInterface::suspend()
{
	if(Tran)
		Tran->Finish();

	DF->Suspend();	
	Materials->ReadAllMaterials();    
//TODO detatch from df aswell/instead of throw
	if(!Creatures->Start(numCreatures))
		throw RSException();    

//	if(!numCreatures)
//		throw RSException();

	if(!Tran->Start())
		throw RSException();

	suspended = true;
}

void DFInterface::process()
{
	cleanup();
	currentYear = world->ReadCurrentYear();
	dwarfCivID = Creatures->GetDwarfCivId();
	raceExCache =  Materials->raceEx;
	organicMatCache = Materials->organic;
	inorganicMatCache = Materials->inorganic;

	for(int i=0; i<numCreatures; i++)
	{
		DFHack::t_creature rTemp;
		Creatures->ReadCreature(i, rTemp);
		RSCreature *temp = new RSCreature(rTemp, i, this);

		if(QString(Materials->raceEx[rTemp.race].rawname) == mainRace)
		{
			if(!rTemp.flags1.bits.dead)
				dwarves.push_back(temp);
		
			allDwarves.push_back(temp);
		}
		else
		{
			if(!rTemp.flags1.bits.dead)
				creatures.push_back(temp);
			
			allCreatures.push_back(temp);
		}	
	}	
}

QString DFInterface::translateName(DFHack::t_name const& name, bool english)
{
	return Tran->TranslateName(name, english).c_str();
}

QString DFInterface::translateSkill(const uint32_t skill)
{
	if(isAttached())
	{
		try
		{
			return mem->getSkill(skill).c_str();
		}
		catch(std::exception &e)
		{
		}
	}
	
	return "";
}

QString DFInterface::translateProfession(const uint32_t prof)
{
	if(isAttached())
	{
		try
		{
			return mem->getProfession(prof).c_str();
		}
		catch(std::exception &e)
		{
		}
	}
	
	return "";
}

QString DFInterface::translateRace(const uint32_t race)
{
	return raceExCache[race].rawname;
}

uint32_t DFInterface::getRacialAverage(uint32_t race, uint32_t caste, RacialStat stat)
{
	if(isAttached())
	{
		switch(stat)
		{
		case STRENGTH_STAT:
			return raceExCache[race].castes[caste].strength.level;
		case AGILITY_STAT:
			return raceExCache[race].castes[caste].agility.level;
		case TOUGHNESS_STAT:
			return raceExCache[race].castes[caste].toughness.level;
		case ENDURANCE_STAT:
			return raceExCache[race].castes[caste].endurance.level;
		case RECUPERATION_STAT:
			return raceExCache[race].castes[caste].recuperation.level;
		case DISEASE_RESISTANCE_STAT:
			return raceExCache[race].castes[caste].disease_resistance.level;
		case WILLPOWER_STAT:
			return raceExCache[race].castes[caste].willpower.level;
		case MEMORY_STAT:
			return raceExCache[race].castes[caste].memory.level;
		case FOCUS_STAT:
			return raceExCache[race].castes[caste].focus.level;
		case INTUITION_STAT:
			return raceExCache[race].castes[caste].intuition.level;
		case PATIENCE_STAT:
			return raceExCache[race].castes[caste].patience.level;
		case EMPATHY_STAT:
			return 0;//raceExCache[race].castes[caste].empathy.level;
		case SOCIAL_AWARENESS_STAT:
			return 0;//raceExCache[race].castes[caste].social_awareness.level;
		case CREATVITY_STAT:
			return raceExCache[race].castes[caste].creativity.level;
		case MUSICALITY_STAT:
			return raceExCache[race].castes[caste].musicality.level;
		case ANALYTICAL_ABILITY_STAT:
			return raceExCache[race].castes[caste].analytical_ability.level;
		case LINGUISTIC_ABILITY_STAT:
			return raceExCache[race].castes[caste].linguistic_ability.level;
		case SPATIAL_SENSE_STAT:
			return raceExCache[race].castes[caste].spatial_sense.level;
		case KINESTHETIC_SENSE_STAT:
			return raceExCache[race].castes[caste].kinesthetic_sense.level;
		default: 
			return 0;
		}
	}
	else
		return 0;
}

DFHack::t_level DFInterface::getLevelInfo(uint32_t level)
{
	if(isAttached())
	{
		try
		{
			return mem->getLevelInfo(level);
		}
		catch(std::exception &e)
		{
		}
	}

	DFHack::t_level tmpLvl;
	tmpLvl.level = level;
	tmpLvl.name = "Unknown";
	tmpLvl.xpNxtLvl = 0;
	return tmpLvl;	
}

QString DFInterface::translateLabour(const uint8_t labour)
{
	if(isAttached())
	{
		try
		{
			return mem->getLabor(labour).c_str();
		}
		catch(std::exception &e)
		{//TODO add logging class
			return e.what();
		}
	}
	
	return "";
}

QString DFInterface::translateTrait(uint32_t index, uint32_t value)
{
	if(isAttached())
	{
		try
		{
			return mem->getTrait(index, value).c_str();
		}
		catch(std::exception &e)
		{
		}
	}
	
	return "";
}

void DFInterface::setProcessDead(bool state)
{
	processDead = state;
}

QString DFInterface::getVersion()
{
	if(isAttached())
	{
		try
		{
			return mem->getVersion().c_str();
		}
		catch(std::exception &e)
		{
		}
	}
	
	return "";
}

uint32_t DFInterface::getCurrentYear()
{
	return currentYear;
}

void DFInterface::cleanup()
{
	for(int i=0; i<allCreatures.size(); i++)
	{
		if(allCreatures[i])
			delete allCreatures[i];
	}

	allCreatures.clear();
	creatures.clear();

	for(int i=0; i<allDwarves.size(); i++)
	{
		if(allDwarves[i])
			delete allDwarves[i];
	}

	allDwarves.clear();
	dwarves.clear();
	raceExCache.clear();
	organicMatCache.clear();
	inorganicMatCache.clear();
}

bool DFInterface::changesPending()
{
	std::vector<RSCreature*>::size_type size = allDwarves.size();

	for(int i=0; i<size; i++)
	{
		if(allDwarves[i]->isChanged())
			return true;
	}

	size = allCreatures.size();

	for(int i=0; i<size; i++)
	{
		if(allCreatures[i]->isChanged())
			return true;
	}

	return false;
}

bool DFInterface::writeAllChanges()
{
	if(isContextValid())
	{
		if(isAttached())
		{
			suspend();

			try
			{
				if(internalWriteChanges())
				{
					process();
					resume();
					return true;
				}
				else
				{
					process();
					resume();
					return false;
				}
			}
			catch(std::exception &e)
			{
			}
		}
	}

	return false;
}

bool DFInterface::internalWriteChanges()
{
	if(!writeLoop(allDwarves))
		return false;

	if(!writeLoop(allCreatures))
		return false;

	return true;
}

bool DFInterface::writeLoop(std::vector<RSCreature*> &data)
{
	for(int i=0; i<data.size(); i++)
	{
		uint32_t rawID = data[i]->getID();
		statusTracker const& rawStatus = data[i]->getChanged();
		DFHack::t_creature const& rawData = data[i]->getRawCreature();

		if(rawStatus.happinessChanged)
		{
			if(!Creatures->WriteHappiness(rawID, rawData.happiness))
				return false;
		}

		if(rawStatus.skillsChanged)
		{
			if(!Creatures->WriteSkills(rawID, rawData.defaultSoul))
				return false;
		}

		if(rawStatus.attributesChanged)
		{
			if(!Creatures->WriteAttributes(rawID, data[i]->getRawCreature()))
				return false;
		}

		if(rawStatus.flagsChanged)
		{
			if(!Creatures->WriteFlags(rawID, 
				rawData.flags1.whole,
				rawData.flags2.whole))

				return false;
		}

		if(rawStatus.sexChanged)
		{
			if(!Creatures->WriteSex(rawID, rawData.sex))
				return false;
		}

		if(rawStatus.traitsChanged)
		{
			if(!Creatures->WriteTraits(rawID, rawData.defaultSoul))
				return false;
		}

		if(rawStatus.moodChanged)
		{
			if(!Creatures->WriteMood(rawID, rawData.mood))
				return false;

			if(!Creatures->WriteMoodSkill(rawID, rawData.mood_skill))
				return false;

			if(!Creatures->WriteJob(&rawData, data[i]->getRawMats()))
				return false;
		}

		if(rawStatus.posChanged)
		{
			if(!Creatures->WritePos(rawID, data[i]->getRawCreature()))
				return false;
		}

		if(rawStatus.civChanged)
		{
			if(!Creatures->WriteCiv(rawID, rawData.civ))
				return false;
		}

		if(rawStatus.laboursChanged)
		{
			if(!Creatures->WriteLabors(rawID, ((DFHack::t_creature)rawData).labors))
				return false;
		}

		data[i]->resetFlags();
	}
	return true;
}

std::vector< std::vector<std::string> > const& DFInterface::getAllTraits()
{
	return mem->getAllTraits();
}

std::map<uint32_t, std::string> const& DFInterface::getAllLabours()
{
	return mem->getAllLabours();
}

bool DFInterface::readMats(const DFHack::t_creature *creature, std::vector<DFHack::t_material> &mats)
{
	if(isContextValid())
	{
		if(isAttached())
		{
			//suspend();

			try
			{
				Creatures->ReadJob(creature, mats);
			}
			catch(std::exception &e)
			{
				//resume();
				return false;
			}
			
			//resume();
			return true;			
		}
	}

	return false;
}

QString DFInterface::getMatDescription(DFHack::t_material &mat)
{
	if(isAttached())
	{
		try
		{
			if(!suspended)
			{
				suspend();
				QString temp = Materials->getDescription(mat).c_str();
				resume();
				return temp;
			}
			else
				return Materials->getDescription(mat).c_str();
		}
		catch(std::exception &e)
		{
		}
	}
	
	return "";
}

QString DFInterface::getMood(uint32_t mood)
{
	if(isAttached())
	{
		try
		{
			return mem->getMood(mood).c_str();
		}
		catch(std::exception &e)
		{
		}
	}
	
	return "";
}

std::vector<DFHack::t_matgloss> const& DFInterface::getOrganicMats()
{
	return organicMatCache;
}

std::vector<DFHack::t_matgloss> const& DFInterface::getInorgaincMats()
{
	return inorganicMatCache;
}

void DFInterface::setMainRace(QString nMainRace)
{
	mainRace = nMainRace.toUpper();
	mainRace = mainRace.trimmed();
}

int32_t DFInterface::getDwarfCiv()
{
	return dwarfCivID;
}

void DFInterface::setAllRaceSkills(uint8_t val)
{
	for(int i=0; i<dwarves.size(); i++)
	{
		dwarves[i]->setAllSkillLevels(val);
	}
}

void DFInterface::setAllRaceAttrs(uint16_t val)
{
	for(int i=0; i<dwarves.size(); i++)
	{
		dwarves[i]->setAllAttributes(val);
	}
}

void DFInterface::killAllRace(uint32_t race)
{
	std::vector<RSCreature*>::iterator iter = creatures.begin();

	while(iter != creatures.end())
	{
		if((*iter)->getRawCreature().race == race)
			iter = creatures.erase(iter);
		else
			iter++;
	}
}

QString DFInterface::getMaterialType(DFHack::t_material &mat)
{
	if(isAttached())
	{
		try
		{
			return Materials->getType(mat).c_str();
		}
		catch(std::exception &e)
		{
		}
	}
	
	return "";
}

void DFInterface::sortDwarvesByName(bool decending)
{
	if(decending)
	{
		if(!processDead)
			std::sort(dwarves.begin(), dwarves.end(), creatureDecNameCmp);
		else
			std::sort(allDwarves.begin(), dwarves.end(), creatureDecNameCmp);	
	}
	else
	{
		if(!processDead)
			std::sort(dwarves.begin(), dwarves.end(), creatureAscNameCmp);
		else
			std::sort(allDwarves.begin(), dwarves.end(), creatureAscNameCmp);
	}
}

void DFInterface::sortDwarvesByProf(bool decending)
{
	if(decending)
	{
		if(!processDead)
			std::sort(dwarves.begin(), dwarves.end(), creatureDecProfCmp);
		else
			std::sort(allDwarves.begin(), dwarves.end(), creatureDecProfCmp);	
	}
	else
	{
		if(!processDead)
			std::sort(dwarves.begin(), dwarves.end(), creatureAscProfCmp);
		else
			std::sort(allDwarves.begin(), dwarves.end(), creatureAscProfCmp);
	}
}

void DFInterface::sortDwarvesByHap(bool decending)
{
	if(decending)
	{
		if(!processDead)
			std::sort(dwarves.begin(), dwarves.end(), creatureDecHapCmp);
		else
			std::sort(allDwarves.begin(), dwarves.end(), creatureDecHapCmp);	
	}
	else
	{
		if(!processDead)
			std::sort(dwarves.begin(), dwarves.end(), creatureAscHapCmp);
		else
			std::sort(allDwarves.begin(), dwarves.end(), creatureAscHapCmp);
	}
}

void DFInterface::sortCreaturesByRace(bool decending)
{
	if(decending)
	{
		if(!processDead)
			std::sort(creatures.begin(), creatures.end(), creatureDecRaceCmp);
		else
			std::sort(allCreatures.begin(), creatures.end(), creatureDecRaceCmp);	
	}
	else
	{
		if(!processDead)
			std::sort(creatures.begin(), creatures.end(), creatureAscRaceCmp);
		else
			std::sort(allCreatures.begin(), creatures.end(), creatureAscRaceCmp);
	}
}

void DFInterface::sortCreaturesByName(bool decending)
{
	if(decending)
	{
		if(!processDead)
			std::sort(creatures.begin(), creatures.end(), creatureDecNameCmp);
		else
			std::sort(allCreatures.begin(), creatures.end(), creatureDecNameCmp);	
	}
	else
	{
		if(!processDead)
			std::sort(creatures.begin(), creatures.end(), creatureAscNameCmp);
		else
			std::sort(allCreatures.begin(), creatures.end(), creatureAscNameCmp);
	}
}

void DFInterface::sortCreaturesByProf(bool decending)
{
	if(decending)
	{
		if(!processDead)
			std::sort(creatures.begin(), creatures.end(), creatureDecProfCmp);
		else
			std::sort(allCreatures.begin(), creatures.end(), creatureDecProfCmp);	
	}
	else
	{
		if(!processDead)
			std::sort(creatures.begin(), creatures.end(), creatureAscProfCmp);
		else
			std::sort(allCreatures.begin(), creatures.end(), creatureAscProfCmp);
	}
}

void DFInterface::sortCreaturesByHap(bool decending)
{
	if(decending)
	{
		if(!processDead)
			std::sort(creatures.begin(), creatures.end(), creatureDecHapCmp);
		else
			std::sort(allCreatures.begin(), creatures.end(), creatureDecHapCmp);	
	}
	else
	{
		if(!processDead)
			std::sort(creatures.begin(), creatures.end(), creatureAscHapCmp);
		else
			std::sort(allCreatures.begin(), creatures.end(), creatureAscHapCmp);
	}
}
