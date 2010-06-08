#include "DFInterface.h"
#include "rsException.h"

DFInterface::DFInterface(void) : DF(NULL),
	DFMgr(NULL), Materials(NULL), Tran(NULL), Creatures(NULL), mem(NULL)
{
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
}

bool DFInterface::isAttached()
{
	if(DF)
		return DF->isAttached();
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
			creatures.clear();
			dwarves.clear();
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
		creatures.clear();
		dwarves.clear();
	}
}

std::vector<DFHack::t_creature>& DFInterface::getDwarves()
{
	if(isAttached())
		return dwarves;
	else
	{
		dwarves.clear();
		creatures.clear();
		return dwarves;
	}
}

std::vector<DFHack::t_creature>& DFInterface::getCreatures()
{
	if(isAttached())
		return creatures;
	else
	{
		dwarves.clear();
		creatures.clear();
		return creatures;
	}
}

DFHack::t_creature* DFInterface::getDwarf(int dwarf)
{
	if(isAttached())
		return &dwarves[dwarf];
	else
		return NULL;
}

DFHack::t_creature* DFInterface::getCreature(int creature)
{
	if(isAttached())
		return &creatures[creature];
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

	if(!Creatures->Start(numCreatures))
		throw RSException();    

	if(!numCreatures)
		throw RSException();

	if(!Tran->Start())
		throw RSException();
}

void DFInterface::process()
{
	creatures.clear();
	dwarves.clear();

	for(int i=0; i<numCreatures; i++)
	{
		DFHack::t_creature temp;
		Creatures->ReadCreature(i,temp);

		if(QString(Materials->raceEx[temp.race].rawname) == "DWARF")
		{
			dwarves.push_back(temp);
		}
		else
		{
			creatures.push_back(temp);
		}
	}	
}

QString DFInterface::translateName(const DFHack::t_name &name)
{
	if(isAttached())
	{
		return Tran->TranslateName(name, false).c_str();		 
	}
	else
		return "";
}

QString DFInterface::translateSkill(const uint32_t skill)
{
	if(isAttached())
		return mem->getSkill(skill).c_str();
	else
		return "";
}

QString DFInterface::translateProfession(const uint32_t prof)
{
	if(isAttached())
		return mem->getProfession(prof).c_str();
	else
		return "";
}

QString DFInterface::translateRace(const uint32_t race)
{
	if(isAttached())
		return Materials->raceEx[race].rawname;
	else
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
