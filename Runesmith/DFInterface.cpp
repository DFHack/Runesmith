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
	if(isContextValid())
	{
		return DF->isAttached();
	}
	else
		return false;
}

bool DFInterface::isContextValid()
{
	if(!DF)
		return false;
/*
	DFHack::BadContexts inval;
	DFMgr->Refresh(&inval);
	return !inval.Contains(DF);*/
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
	if(isAttached())
	{				
		suspend();
		DF->Detach();
		numCreatures = 0;
		creatures.clear();
		dwarves.clear();
	}
}

void DFInterface::update()
{
	if(isAttached())
	{
		suspend();
		process();
		resume();
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
