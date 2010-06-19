#include "DFInterface.h"
#include "rsException.h"

DFInterface::DFInterface(void) : DF(NULL), DFMgr(NULL), Materials(NULL), Tran(NULL),
	Creatures(NULL), mem(NULL), processDead(false), dataChanged(false)
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
			dataChanged = false;
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
		dataChanged = false;
		numCreatures = 0;
		cleanup();
	}
}

std::vector<DFHack::t_creature *>& DFInterface::getDwarves()
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

std::vector<DFHack::t_creature *>& DFInterface::getCreatures()
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

DFHack::t_creature* DFInterface::getDwarf(uint32_t dwarf)
{
	if(isAttached())
		if(!processDead)
			return dwarves[dwarf];
		else
			return allDwarves[dwarf];
	else
		return NULL;
}

DFHack::t_creature* DFInterface::getCreature(uint32_t creature)
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
}

void DFInterface::suspend()
{
	if(Tran)
		Tran->Finish();

	DF->Suspend();	
	Materials->ReadAllMaterials();    
//FIXME detatch from df aswell/instead of throw
	if(!Creatures->Start(numCreatures))
		throw RSException();    

	if(!numCreatures)
		throw RSException();

	if(!Tran->Start())
		throw RSException();
}

void DFInterface::process()
{
	cleanup();
	currentYear = world->ReadCurrentYear();

	for(int i=0; i<numCreatures; i++)
	{
		DFHack::t_creature *temp = new DFHack::t_creature;
		Creatures->ReadCreature(i,*temp);
		changeTracker[temp->id].id = i;
		
		if((temp->mood > -1) && (temp->mood < 6))
		{
			std::vector<DFHack::t_material> tmats;
			readMats(temp, tmats);
			moods[temp->id] = tmats;
		}

		if(QString(Materials->raceEx[temp->race].rawname) == mainRace)
		{
			if(!temp->flags1.bits.dead)
				dwarves.push_back(temp);
		
			allDwarves.push_back(temp);
		}
		else
		{
			if(!temp->flags1.bits.dead)
				creatures.push_back(temp);
			
			allCreatures.push_back(temp);
		}	
	}	
}

std::vector<DFHack::t_material>& DFInterface::getMoodMats(uint32_t id)
{
	return moods[id];
}

QString DFInterface::translateName(const DFHack::t_name &name, bool english)
{
	if(isAttached())
	{
		try
		{
			return Tran->TranslateName(name, english).c_str();
		}
		catch(std::exception &e)
		{
		}
	}
	
	return "";
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
	if(isAttached())
	{
		try
		{
			return Materials->raceEx[race].rawname;
		}
		catch(std::exception &e)
		{
		}
	}
	
	return "";
}

uint32_t DFInterface::getRacialAverage(uint32_t race, uint32_t caste, RacialStat stat)
{
	if(isAttached())
	{
		switch(stat)
		{
		case STRENGTH_STAT:
			return Materials->raceEx[race].castes[caste].strength.level;
		case AGILITY_STAT:
			return Materials->raceEx[race].castes[caste].agility.level;
		case TOUGHNESS_STAT:
			return Materials->raceEx[race].castes[caste].toughness.level;
		case ENDURANCE_STAT:
			return Materials->raceEx[race].castes[caste].endurance.level;
		case RECUPERATION_STAT:
			return Materials->raceEx[race].castes[caste].recuperation.level;
		case DISEASE_RESISTANCE_STAT:
			return Materials->raceEx[race].castes[caste].disease_resistance.level;
		case WILLPOWER_STAT:
			return Materials->raceEx[race].castes[caste].willpower.level;
		case MEMORY_STAT:
			return Materials->raceEx[race].castes[caste].memory.level;
		case FOCUS_STAT:
			return Materials->raceEx[race].castes[caste].focus.level;
		case INTUITION_STAT:
			return Materials->raceEx[race].castes[caste].intuition.level;
		case PATIENCE_STAT:
			return Materials->raceEx[race].castes[caste].patience.level;
		case CREATVITY_STAT:
			return Materials->raceEx[race].castes[caste].creativity.level;
		case MUSICALITY_STAT:
			return Materials->raceEx[race].castes[caste].musicality.level;
		case ANALYTICAL_ABILITY_STAT:
			return Materials->raceEx[race].castes[caste].analytical_ability.level;
		case LINGUISTIC_ABILITY_STAT:
			return Materials->raceEx[race].castes[caste].linguistic_ability.level;
		case SPATIAL_SENSE_STAT:
			return Materials->raceEx[race].castes[caste].spatial_sense.level;
		case KINESTHETIC_SENSE_STAT:
			return Materials->raceEx[race].castes[caste].kinesthetic_sense.level;
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
		{
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
		if(allCreatures[i])
			delete allCreatures[i];
	allCreatures.clear();
	creatures.clear();

	for(int i=0; i<allDwarves.size(); i++)	
		if(allDwarves[i])
			delete allDwarves[i];
	allDwarves.clear();
	dwarves.clear();

	changeTracker.clear();
	moods.clear();
	dataChanged = false();
}

void DFInterface::setChanged(uint32_t id, TrackedBlocks changedBlock)
{
	switch(changedBlock)
	{
	case HAPPINESS_CHANGED: 
		changeTracker[id].happinessChanged = true; 
		break;

	case FLAGS_CHANGED:	
		changeTracker[id].flagsChanged = true; 
		break;

	case ATTRIBUTES_CHANGED: 
		changeTracker[id].attributesChanged = true;
		break;

	case SKILLS_CHANGED: 
		changeTracker[id].skillsChanged = true;
		break;

	case SEX_CHANGED:
		changeTracker[id].sexChanged = true;
		break;

	case TRAITS_CHANGED:
		changeTracker[id].traitsChanged = true;
		break;

	case MOOD_CHANGED:
		changeTracker[id].moodChanged = true;
		break;
	}

	dataChanged = true;
}

bool DFInterface::changesPending()
{
	return dataChanged;
}

bool DFInterface::writeAllChanges()
{
	if(!dataChanged)
		return true;

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

	return true;
}

bool DFInterface::internalWriteChanges()
{
	if(!writeLoop(allDwarves))
		return false;

	if(!writeLoop(allCreatures))
		return false;

	dataChanged = false;
	return true;
}

bool DFInterface::writeLoop(std::vector<DFHack::t_creature *> &data)
{
	for(int i=0; i<data.size(); i++)
	{
		statusTracker &temp = changeTracker[data[i]->id];

		if(temp.happinessChanged)
		{
			if(!Creatures->WriteHappiness(temp.id, data[i]->happiness))
				return false;

			temp.happinessChanged = false;
		}

		if(temp.skillsChanged)
		{
			if(!Creatures->WriteSkills(temp.id, data[i]->defaultSoul))
				return false;

			temp.skillsChanged = false;
		}

		if(temp.attributesChanged)
		{
			if(!Creatures->WriteAttributes(temp.id, *data[i]))
				return false;

			temp.attributesChanged = false;
		}

		if(temp.flagsChanged)
		{
			if(!Creatures->WriteFlags(temp.id, data[i]->flags1.whole, data[i]->flags2.whole))
				return false;

			temp.flagsChanged = false;
		}

		if(temp.sexChanged)
		{
			if(!Creatures->WriteSex(temp.id, data[i]->sex))
				return false;

			temp.sexChanged = false;
		}

		if(temp.traitsChanged)
		{
			if(!Creatures->WriteTraits(temp.id, data[i]->defaultSoul))
				return false;

			temp.traitsChanged = false;
		}

		if(temp.moodChanged)
		{
			if(!Creatures->WriteMood(temp.id, data[i]->mood))
				return false;

			temp.moodChanged = false;
		}
	}

	return true;
}

std::vector< std::vector<std::string>> const& DFInterface::getAllTraits()
{
	return mem->getAllTraits();
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
	return Materials->organic;
}

std::vector<DFHack::t_matgloss> const& DFInterface::getInorgaincMats()
{
	return Materials->inorganic;
}

void DFInterface::setMainRace(QString nMainRace)
{
	mainRace = nMainRace.toUpper();
}
